#include "Game.h"

#include <fstream>
#include <sstream>

Game::Game(unsigned int Width, unsigned int Height)
	: State(WaitingToStart), Width(Width), Height(Height) {}

void Game::Initialize() 
{
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("../Resources/Fonts/OtomanopeeOne.ttf", 24);

	ResourceManager::LoadShader("../Resources/Shaders/Vertex.txt", "../Resources/Shaders/Fragment.txt", nullptr, "Sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Width),
		static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	
	ResourceManager::GetShader("Sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("Sprite").SetMatrix4("projection", projection);
	
	Sprite = new SpriteRenderer(ResourceManager::GetShader("Sprite"));

	ResourceManager::LoadTexture("../Resources/Textures/BG.png", true, "BG");
	ResourceManager::LoadTexture("../Resources/Textures/Obstacle.png", true, "Obstacle");
	ResourceManager::LoadTexture("../Resources/Textures/Jellyfish.png", true, "Player");

	BackGround = new Actor(glm::vec2(0.0f, 0.0f), glm::vec2(Width, Height), ResourceManager::GetTexture("BG"));

	glm::vec2 PlayerPos = glm::vec2(PlayerSize.x, Height / 2.0f - PlayerSize.y / 2.0f);
	CurrentPlayer = new Player(PlayerPos, PlayerSize, ResourceManager::GetTexture("Player"),
								static_cast<float>(Height) - PlayerSize.y/2.0f);
	

	ObstaclesGen = new ObstaclesGenerator(0, Height, Width);
	Obstacles.clear();
	AddObstacle();
	Score = 0;
	IsHighResult = false;
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

	PlayerVelocity += GameSpeedIncrement;
	ObstacleVelocity += GameSpeedIncrement;
}

void Game::ScoreCounting(Obstacle* DetectionObstacle)
{
	if (!DetectionObstacle->IsObstacleChecked()
		&& CurrentPlayer->GetPosition().x >= DetectionObstacle->GetPosition().x + ObstaclesGen->ObstacleWidth)
	{
		Score++;
		DetectionObstacle->SetObstacleChecked();
	}
}

void Game::ShowHighScores()
{
	Text->RenderText("Highscores" , Width / 2 - 70, Height / 2 - 130, 1.2f);

	auto ScoreTable = GetHighScoreList();
	int Number = 0;
	float TableRowSize = Height / 2 - 90.0f;

	if (IsHighResult)
	{
		for (auto it = ScoreTable.begin(); it != ScoreTable.end(); ++it)
		{
			Number++;
			std::stringstream TableName, TableScore;
			TableName << it->second;
			TableScore << it->first;
			Text->RenderText(std::to_string(Number) + ". " + TableName.str() + ": " + TableScore.str(), Width/2 - 60, TableRowSize, 1.0f);
			TableRowSize += 25;
		}
	}
	else
	{
		for (auto it = ScoreTable.begin(); it != ScoreTable.end(); ++it)
		{
			Number++;
			std::stringstream TableName, TableScore;
			TableName << it->second;
			TableScore << it->first;
			Text->RenderText(std::to_string(Number) + ". " + TableName.str() + ": " + TableScore.str(), Width / 2 - 60, TableRowSize, 1.0f);
			TableRowSize += 25.0f;
		}

		if (State != GameState::GameOver) return;

		std::stringstream PlayerScore;
		PlayerScore << Score;
		Text->RenderText("...", Width / 2.0f, TableRowSize, 1.0f);
		Text->RenderText(PlayerName + ": " + PlayerScore.str(), Width / 2 - 60, TableRowSize + 25, 1.0f);
	}
}

void Game::SaveCurrentScoreIfRequired()
{
	std::ofstream HighScores("HighScores.txt", std::ios_base::app);
	if (!HighScores.is_open() || Score == 0 ) return;

	auto ScoreTable = GetHighScoreList();

	if (ScoreTable.empty())
	{
		IsHighResult = true;
		HighScores << PlayerName << ":";
		HighScores << Score << "|";
		HighScores.close();
	}

	for (auto it = ScoreTable.begin(); it != ScoreTable.end(); ++it)
	{
		if (Score >= it->first || ScoreTable.size() < 5)
		{
			IsHighResult = true;
			HighScores << PlayerName << ":";
			HighScores << Score << "|";
			HighScores.close();
			break;
		}
	}
}

std::multimap<unsigned int, std::string, std::greater<int>> Game::GetHighScoreList()
{
	std::multimap<unsigned int, std::string, std::greater<int>> ScoreTable;
	std::fstream HighScores("HighScores.txt");

	auto Buffer = std::ostringstream{};
	if (HighScores.is_open())
	{
		Buffer << HighScores.rdbuf();
		std::string Values = Buffer.str();
		std::string Delimiter = "|";
		size_t Pos = 0;

		while ((Pos = Values.find(Delimiter)) != std::string::npos)
		{
			auto PlayerScore = Values.substr(0, Pos);
			auto Name = PlayerScore.substr(0, PlayerScore.find(":"));
			auto Value = PlayerScore.substr(PlayerScore.find(":")+1);
			ScoreTable.insert(std::pair<unsigned int, std::string>(std::stoi(Value), Name));
			Values.erase(0, Pos + Delimiter.length());
		}
	}
	HighScores.close();

	HighScores.open("HighScores.txt", std::ios_base::out | std::ios_base::trunc);
	HighScores.close();

	HighScores.open("HighScores.txt", std::ios_base::app);
	int i = 0;
	for (auto it = ScoreTable.begin(); it != ScoreTable.end(); ++it)
	{
		i++;
		if (i > 5)
		{
			ScoreTable.erase(it, ScoreTable.end());
			break;
		}
	}

	for (auto it = ScoreTable.begin(); it != ScoreTable.end(); ++it)
	{
		HighScores << it->second << ":";
		HighScores << it->first << "|";
	}
	HighScores.close();

	return ScoreTable;
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
	SaveCurrentScoreIfRequired();
	State = GameState::GameOver;
}

void Game::ProcessInput(int Key, int Action)
{

	if (Key == GLFW_KEY_SPACE && Action == GLFW_PRESS)
	{
		switch (State) 
		{
		case InProgress:
			CurrentPlayer->Up();
			break;
		case WaitingToStart:
			Initialize();
			State = InProgress;
			break;
		case Pause:
			State = InProgress;
			break;
		case GameState::GameOver:
			Initialize();
			State = InProgress;
			break;
		}
	}
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
	{
		switch (State)
		{
		case InProgress:
			State = Pause;
			break;
		case Pause:
			Initialize();
			State = WaitingToStart;
			break;
		default:
			State = WaitingToStart;
			break;
		}
	}
	if (Key == GLFW_KEY_M && Action == GLFW_PRESS && State == WaitingToStart)
	{
		State = AdditionlMenuOpened;
	}
	if (Key == GLFW_KEY_N && Action == GLFW_PRESS && State == WaitingToStart)
	{
		State = NameInput;
	}
	if (State == NameInput && Action == GLFW_PRESS)
	{
		if (Key == GLFW_KEY_ENTER)
		{
			State = WaitingToStart;
		}
		else if (Key == GLFW_KEY_BACKSPACE)
		{
			PlayerName = PlayerName.substr(0, PlayerName.length() - 1);
		}
		else if (Key >= GLFW_KEY_A && Key <= GLFW_KEY_Z && PlayerName.length() < 6)
		{
			PlayerName += Symbols[Key-GLFW_KEY_A];
		}
	}
}

void Game::Render()
{
	BackGround->Draw(*Sprite);
	CurrentPlayer->Draw(*Sprite);

	for (auto ObstacleItem : Obstacles)
	{
		ObstacleItem->Draw(*Sprite);
	}

	switch (State)
	{
	case InProgress:
		Text->RenderText("Score: " + std::to_string(Score), 10.0f, 10.0f, 1.0f);
		break;
	case Pause:
		Text->RenderText("PAUSE", Width / 2 - 60, Height / 2 - 5, 1.7f);
		Text->RenderText("Press SPACE to return", 265.0f, Height / 2 + 60, 1.0f);
		Text->RenderText("Press ESCAPE to quit", 275.0f, Height / 2 + 120, 1.0f);
		break;
	case WaitingToStart:
		Text->RenderText("Press SPACE to start", 250.0f, Height / 2, 1.0f);
		Text->RenderText("Press M to watch highscores", 200.0f, Height / 2 + 35, 1.0f);
		Text->RenderText("Press N to enter name", 240.0f, Height / 2 + 60, 1.0f);
		break;
	case GameState::GameOver:
		Text->RenderText("GAME OVER", Width / 2 - 115, Height / 2 - 185, 1.7f);
		Text->RenderText("Press SPACE to restart...", Width / 2 - 140, Height / 2 + 150, 1.0f);
		ShowHighScores();
		break;
	case AdditionlMenuOpened:
		ShowHighScores();
		break;
	case NameInput:
		Text->RenderText("Enter your name", Width / 2 - 200, Height / 2 - 165, 1.7f);
		Text->RenderText(PlayerName, Width / 2 - 100, Height / 2 - 125, 1.7f);
		break;
	}
}

Game::~Game()
{
	delete Sprite;
	delete CurrentPlayer;
	delete ObstaclesGen;
	Obstacles.clear();
}
