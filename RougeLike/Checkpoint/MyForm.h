#pragma once
#include "TileViewport.h"
#include "SpriteList.h"
#include "Room.h"
#include "Dungeon.h"
#include "WorldController.h"
#include "Sprite.h"

#define COL 100
#define ROW 50
#define MOVESPEED 16
#define TILEWIDTH 32
#define NPCNUM 20
#define VERTICALRES 1080
#define HORIZONTALRES 1920

//#define NTILES 3 //might not need here


namespace Checkpoint {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::ComponentModel::IContainer^ components;
		/// <summary>
		/// Required designer variable.
		/// </summary>

		Bitmap^ tiles;
		Tile^ tile0, ^ tile1, ^ tile2;
		TileMap^ tileMap;
		Graphics^ mainCanvas;//
		Random^ rGen;//
		//TileViewport^ viewPort;//
		Graphics^ bufferGraphics;
		Bitmap^ bufferImage;
		Sprite^ player;
		SpriteList^ dragons;
		SpriteList^ trolls;
		//Room^ rooms;
		Dungeon^ dunegon;
		array<Room^>^ dunegonRooms;

		Graphics^ canvas;
		Graphics^ bufferCanvas;
		Bitmap^ backgroundBuffer;
		WorldController^ controller;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Panel^  panel1;





#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());

			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(26, 33);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 100);
			this->panel1->TabIndex = 0;
			// 

			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 

			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(1370, 749);

			this->Controls->Add(this->panel1);

			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		mainCanvas = CreateGraphics();

		rGen = gcnew Random();

		bufferImage = gcnew Bitmap(Width, Height);
		bufferGraphics = Graphics::FromImage(bufferImage);
		//viewPort = gcnew TileViewport(0, 0, 30, 20, tileMap, bufferGraphics, TILEWIDTH, COL, ROW);
		//player = generateChickenSprite();
		//player->xPos = 600;
		//player->yPos = 400;
		/*trolls = gcnew SpriteList();
		dragons = gcnew SpriteList();
		for (int i = 0; i < NPCNUM; i++) {
			EnemySprite^ newSprite = generateTrollSprite();
			trolls->AddSprite(newSprite);
		}
		for (int i = 0; i < NPCNUM; i++) {
			EnemySprite^ newSprite = generateDragonSprite();
			dragons->AddSprite(newSprite);
		}*/

		Width = HORIZONTALRES;
		Height = VERTICALRES;
		panel1->Width = Width;
		panel1->Height = Height;

		canvas = panel1->CreateGraphics();
		backgroundBuffer = gcnew Bitmap(panel1->Width, panel1->Height);
		bufferCanvas = Graphics::FromImage(backgroundBuffer);
		controller = gcnew WorldController(bufferCanvas, rGen, panel1->Size);

		timer1->Enabled = true;
	}

	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		controller->KeyDown(e);
		//e->SuppressKeyPress = true;
		///////*switch (e->KeyData)
		//////{
		//////	
		//////case Keys::D:
		//////	player->setDirection(EAST);
		//////	break;
		//////case Keys::S:
		//////	player->setDirection(SOUTH);
		//////	break;
		//////case Keys::A:
		//////	player->setDirection(WEST);
		//////	break;
		//////case Keys::W:
		//////	player->setDirection(NORTH);
		//////	break;
		//////default:
		//////	return;
		//////}
		//////player->Move();*/

		////////viewPort->ViewportDraw();

	}

	//private: Sprite^ generateChickenSprite() {
	//	int framesInChickenSpriteSheet = 8;
	//	int directions = 4;

	//	Bitmap^ east = gcnew Bitmap("Little Chicken Walk East 8.bmp"); //i created a file of backup images if we want to change these <------
	//	Bitmap^ south = gcnew Bitmap("Little Chicken Walk South 8.bmp");
	//	Bitmap^ west = gcnew Bitmap("Little Chicken Walk West 8.bmp");
	//	Bitmap^ north = gcnew Bitmap("Little Chicken Walk North 8.bmp");

	//	array<Bitmap^>^ chickenImages = gcnew array<Bitmap^>(directions);

	//	chickenImages[ESpriteDirections::EAST] = east;
	//	chickenImages[ESpriteDirections::SOUTH] = south;
	//	chickenImages[ESpriteDirections::WEST] = west;
	//	chickenImages[ESpriteDirections::NORTH] = north;

	//	for (int d = 0; d < directions; d++)
	//	{
	//		Color transparentColor = chickenImages[d]->GetPixel(0, 0);
	//		chickenImages[d]->MakeTransparent(transparentColor);
	//	}

	//	return gcnew PlayerSprite(bufferGraphics, chickenImages, framesInChickenSpriteSheet, rGen, TILEWIDTH*COL, TILEWIDTH*ROW, MOVESPEED, tileMap);
	//}
		
	//enemy sprite generator called them "zombies"
	//private: EnemySprite ^ generateTrollSprite() {
	//	int framesSpriteSheet = 13;
	//	int directions = 4;

	//	Bitmap^ east = gcnew Bitmap("Grey Troll East.png");
	//	Bitmap^ south = gcnew Bitmap("Grey Troll South.png");
	//	Bitmap^ west = gcnew Bitmap("Grey Troll West.png");
	//	Bitmap^ north = gcnew Bitmap("Grey Troll North.png");

	//	array<Bitmap^>^ enemyImages = gcnew array<Bitmap^>(directions);

	//	enemyImages[ESpriteDirections::EAST] = east;
	//	enemyImages[ESpriteDirections::SOUTH] = south;
	//	enemyImages[ESpriteDirections::WEST] = west;
	//	enemyImages[ESpriteDirections::NORTH] = north;

	//	for (int d = 0; d < directions; d++)
	//	{
	//		Color transparentColor = enemyImages[d]->GetPixel(0, 0);
	//		enemyImages[d]->MakeTransparent(transparentColor);
	//	}

	//	return gcnew EnemySprite(bufferGraphics, enemyImages, framesSpriteSheet, rGen, TILEWIDTH*COL, TILEWIDTH*ROW, MOVESPEED, tileMap);//note: returns "EnemySprite"
	//}

	//private: EnemySprite ^ generateDragonSprite() {
	//	int framesSpriteSheet = 9;
	//	int directions = 4;

	//	Bitmap^ east = gcnew Bitmap("Fire Dragon East.bmp");
	//	Bitmap^ south = gcnew Bitmap("Fire Dragon South.bmp");
	//	Bitmap^ west = gcnew Bitmap("Fire Dragon West.bmp");
	//	Bitmap^ north = gcnew Bitmap("Fire Dragon North.bmp");

	//	array<Bitmap^>^ enemyImages = gcnew array<Bitmap^>(directions);

	//	enemyImages[ESpriteDirections::EAST] = east;
	//	enemyImages[ESpriteDirections::SOUTH] = south;
	//	enemyImages[ESpriteDirections::WEST] = west;
	//	enemyImages[ESpriteDirections::NORTH] = north;

	//	for (int d = 0; d < directions; d++)
	//	{
	//		Color transparentColor = enemyImages[d]->GetPixel(0, 0);
	//		enemyImages[d]->MakeTransparent(transparentColor);
	//	}

	//	return gcnew EnemySprite(bufferGraphics, enemyImages, framesSpriteSheet, rGen, TILEWIDTH*COL, TILEWIDTH*ROW, MOVESPEED, tileMap);//note: returns "EnemySprite"
	//}


	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

		bufferCanvas->FillRectangle(Brushes::Transparent, 0, 0, Width, Height);
		controller->RunGameCycle();
		canvas->DrawImage(backgroundBuffer, 0, 0);

		/*player->Collision();
		player->UpdateFrame();*/
		//viewPort->MoveRelativeToPlayer(player->xPos, player->yPos);
		//viewPort->ViewportDraw();
		/*int forcedX, forcedY;

		if (player->xPos < ClientSize.Width / 2)
			forcedX = player->xPos;
		else if (player->xPos + ClientSize.Width / 2 > COL * TILEWIDTH)
			forcedX = player->xPos + ClientSize.Width - COL * TILEWIDTH;
		else
			forcedX = ClientSize.Width / 2;

		if (player->yPos < ClientSize.Height / 2)
			forcedY = player->yPos;
		else if (player->yPos + ClientSize.Height / 2 > ROW * TILEWIDTH)
			forcedY = player->yPos + ClientSize.Height - ROW * TILEWIDTH;
		else
			forcedY = ClientSize.Height / 2;*/

		/*player->ForcedDraw(forcedX, forcedY);
		player->SetSpriteRecPos(forcedX, forcedY);*/
		//trolls
		//trolls->WorldCollisions();
		//trolls->CheckInViewport(viewPort->viewportPixelX, viewPort->viewportPixelY, 1300, 780);
		//trolls->UpdateSprite();
		//trolls->DrawSpritesInViewport(viewPort->viewportPixelX, viewPort->viewportPixelY);
		//trolls->CheckCollisions(player);
		//trolls->DeleteAllDeadSprites();
		//trolls->ChaseSprite(player);

		////dragons
		//dragons->WorldCollisions();
		//dragons->CheckInViewport(viewPort->viewportPixelX, viewPort->viewportPixelY, 1300, 780);
		//dragons->UpdateSprite();
		//dragons->DrawSpritesInViewport(viewPort->viewportPixelX, viewPort->viewportPixelY);
		//dragons->CheckCollisions(player);
		//dragons->DeleteAllDeadSprites();
		//dragons->ChaseSprite(player);
		//mainCanvas->DrawImage(bufferImage, 0, 0);

	}
};
}