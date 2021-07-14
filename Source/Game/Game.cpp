#include "Game.h"

#include <fstream>
#include <sstream>

Game::Game(unsigned int Width, unsigned int Height)
	: State(InProgress), Width(Width), Height(Height) {}

void Game::Initialize() 
{
	ResourceManager::LoadShader("../Resources/Shaders/Vertex.txt", "../Resources/Shaders/Fragment.txt", nullptr, "Sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Width),
		static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	
	ResourceManager::GetShader("Sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("Sprite").SetMatrix4("projection", projection);
	
	Sprite = new SpriteRenderer(ResourceManager::GetShader("Sprite"));

	ResourceManager::LoadTexture("../Resources/Textures/Obstacle.png", true, "Obstacle");
	ResourceManager::LoadTexture("../Resources/Textures/Jellyfish.png", true, "Player");
	
	glm::vec2 PlayerPos = glm::vec2(PlayerSize.x, Height / 2.0f - PlayerSize.y / 2.0f);

	CurrentPlayer = new Player(PlayerPos, PlayerSize, ResourceManager::GetTexture("Player"),
								static_cast<float>(Height) - PlayerSize.y/2.0f);
	
	ObstaclesGen = new ObstaclesGenerator(0, Height, Width);
	AddObstacle();
	Score = 0;
	GetHighScoreList();
}

void Game::Tick(float DeltaTime)
{
	if (State != InProgress) return;
	
	if (CurrentPlayer->GetPosition().y <= CurrentPlayer->GetSize().y/2
		|| CurrentPlayer->GetPosition().y >= (Height - CurrentPlayer->GetSize().y/2))
	{
		GameOver();
	}

	CurrentPlayer->Move(glm::vec2(0, PlayerVelocity * DeltaTime));

	if (!Obstacles.empty()
		&& Obstacles.back()->GetPosition().x < (Height - MinDistanceBetweenObstacles))
	{
		AddObstacle();
	}

	for (auto ObstacleItem : Obstacles)
	{
		if (DetectCollision(ObstacleItem))
		{
			GameOver();
		}

		ScoreCounting(ObstacleItem);
		ObstacleItem->Move(glm::vec2(-ObstacleVelocity * DeltaTime, 0));
	}

	if (!Obstacles.empty()
		&& Obstacles[0]->GetPosition().x + ObstaclesGen->ObstacleWidth <= 0)
	{
		Obstacles.erase(Obstacles.begin());
	}
}

void Game::ScoreCounting(Obstacle* DetectionObstacle)
{
	if (!DetectionObstacle->IsObstacleChecked()
		&& CurrentPlayer->GetPosition().x >= DetectionObstacle->GetPosition().x + ObstaclesGen->ObstacleWidth)
	{
		Score++;
		DetectionObstacle->SetObstacleChecked();
		std::cout << Score << std::endl;
	}
}

void Game::SaveCurrentScore()
{
	std::ofstream HighScores("HighScores.txt", std::ios_base::app);
	if (HighScores.is_open())
	{
		HighScores << Score << "|";
		HighScores.close();
	}
}

std::vector<int> Game::GetHighScoreList()
{
	std::vector<int> AllScores;
	auto Buffer = std::ostringstream{};
	std::ifstream HighScores("HighScores.txt");

	if (HighScores.is_open())
	{
		Buffer << HighScores.rdbuf();
	}

	std::string Values = Buffer.str();
	std::string Delimiter = "|";
	std::string SingleValue;
	size_t Pos = 0;

	while ((Pos = Values.find(Delimiter)) != std::string::npos)
	{
		SingleValue = Values.substr(0, Pos);
		AllScores.push_back(std::stoi(SingleValue));
		Values.erase(0, Pos + Delimiter.length());
	}
	std::sort(AllScores.begin(), AllScores.end());
	return AllScores;
}

bool Game::DetectCollision(Obstacle* DetectionObstacle)
{
	bool DetectionX = CurrentPlayer->GetPosition().x + PlayerSize.x >= DetectionObstacle->GetPosition().x
					&& CurrentPlayer->GetPosition().x <= DetectionObstacle->GetPosition().x + ObstaclesGen->ObstacleWidth;

	bool DetectionY = CurrentPlayer->GetPosition().y + PlayerSize.y >= DetectionObstacle->GetPosition().y
					|| CurrentPlayer->GetPosition().y <= DetectionObstacle->GetPosition().y - ObstaclesGen->HoleSize;

	return DetectionX && DetectionY;
}

void Game::AddObstacle()
{
	Obstacles.push_back(ObstaclesGen->CreateObstacle());
}

void Game::GameOver()
{
	SaveCurrentScore();
	std::cout << "GAME OVER" << std::endl;
	State = GameState::GameOver;
}

void Game::ProcessInput(int Key)
{
	if (State != InProgress) return;

	if (Key == GLFW_KEY_SPACE)
	{
		CurrentPlayer->Up();
	}
}

void Game::Render() 
{
	//if (State != InProgress) return;

	CurrentPlayer->Draw(*Sprite);

	for (auto ObstacleItem : Obstacles)
	{
		ObstacleItem->Draw(*Sprite);
	}
}

Game::~Game()
{
	delete Sprite;
	delete CurrentPlayer;
	delete ObstaclesGen;
	Obstacles.clear();
}
