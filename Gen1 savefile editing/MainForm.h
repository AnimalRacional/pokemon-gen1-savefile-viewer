#include "GameOptions.hpp"
#include "StringConverter.hpp"
#include "List.hpp"
#include "PlayTime.hpp"
#include "PokemonBox.hpp"
#include "SaveReader.hpp"
#include "FormatStr.hpp"
#include <fstream>
#pragma once

namespace Gen1savefileediting {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(bool dbug)
		{
			InitializeComponent();
			debugMode = dbug;
		}
	private: System::Windows::Forms::Label^ lblLeagueBeat;
	public:
	private: System::Windows::Forms::Label^ lblPlaytime;
	private: System::Windows::Forms::Label^ lblPlrId;
	private: System::Windows::Forms::Label^ lblPlrStarter;

	protected:
		bool debugMode = false;
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnOpenFile;
	private: System::Windows::Forms::OpenFileDialog^ ofdGetFile;
	private: System::Windows::Forms::GroupBox^ gbParty;
	private: System::Windows::Forms::ListBox^ lsbPartyPokemon;
	private: System::Windows::Forms::GroupBox^ gbBox;
	private: System::Windows::Forms::ListBox^ lsbPCPokemon;
	private: System::Windows::Forms::NumericUpDown^ numCurBox;
	private: System::Windows::Forms::GroupBox^ gpBackpack;
	private: System::Windows::Forms::ListBox^ lsbBackpack;
	private: System::Windows::Forms::GroupBox^ gpItemBox;
	private: System::Windows::Forms::ListBox^ lsbItemBox;
	private: System::Windows::Forms::GroupBox^ gbTrainerInfo;
	private: System::Windows::Forms::Label^ lblName;
	private: System::Windows::Forms::Label^ lblCoins;

	private: System::Windows::Forms::Label^ lblMoney;
	private: System::Windows::Forms::GroupBox^ gbPokedex;
	private: System::Windows::Forms::ListBox^ lbCaught;
	private: System::Windows::Forms::ListBox^ lbSeen;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnOpenFile = (gcnew System::Windows::Forms::Button());
			this->ofdGetFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->gbParty = (gcnew System::Windows::Forms::GroupBox());
			this->lsbPartyPokemon = (gcnew System::Windows::Forms::ListBox());
			this->gbBox = (gcnew System::Windows::Forms::GroupBox());
			this->lsbPCPokemon = (gcnew System::Windows::Forms::ListBox());
			this->numCurBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->gpBackpack = (gcnew System::Windows::Forms::GroupBox());
			this->lsbBackpack = (gcnew System::Windows::Forms::ListBox());
			this->gpItemBox = (gcnew System::Windows::Forms::GroupBox());
			this->lsbItemBox = (gcnew System::Windows::Forms::ListBox());
			this->gbTrainerInfo = (gcnew System::Windows::Forms::GroupBox());
			this->lblCoins = (gcnew System::Windows::Forms::Label());
			this->lblMoney = (gcnew System::Windows::Forms::Label());
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->gbPokedex = (gcnew System::Windows::Forms::GroupBox());
			this->lbCaught = (gcnew System::Windows::Forms::ListBox());
			this->lbSeen = (gcnew System::Windows::Forms::ListBox());
			this->lblPlrStarter = (gcnew System::Windows::Forms::Label());
			this->lblPlrId = (gcnew System::Windows::Forms::Label());
			this->lblPlaytime = (gcnew System::Windows::Forms::Label());
			this->lblLeagueBeat = (gcnew System::Windows::Forms::Label());
			this->gbParty->SuspendLayout();
			this->gbBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numCurBox))->BeginInit();
			this->gpBackpack->SuspendLayout();
			this->gpItemBox->SuspendLayout();
			this->gbTrainerInfo->SuspendLayout();
			this->gbPokedex->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnOpenFile
			// 
			this->btnOpenFile->Location = System::Drawing::Point(12, 12);
			this->btnOpenFile->Name = L"btnOpenFile";
			this->btnOpenFile->Size = System::Drawing::Size(75, 23);
			this->btnOpenFile->TabIndex = 0;
			this->btnOpenFile->Text = L"Open File";
			this->btnOpenFile->UseVisualStyleBackColor = true;
			this->btnOpenFile->Click += gcnew System::EventHandler(this, &MainForm::btnOpenFile_Click);
			// 
			// ofdGetFile
			// 
			this->ofdGetFile->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::getFile_FileOk);
			// 
			// gbParty
			// 
			this->gbParty->Controls->Add(this->lsbPartyPokemon);
			this->gbParty->Location = System::Drawing::Point(12, 41);
			this->gbParty->Name = L"gbParty";
			this->gbParty->Size = System::Drawing::Size(303, 212);
			this->gbParty->TabIndex = 1;
			this->gbParty->TabStop = false;
			this->gbParty->Text = L"Party";
			// 
			// lsbPartyPokemon
			// 
			this->lsbPartyPokemon->FormattingEnabled = true;
			this->lsbPartyPokemon->Location = System::Drawing::Point(6, 19);
			this->lsbPartyPokemon->Name = L"lsbPartyPokemon";
			this->lsbPartyPokemon->Size = System::Drawing::Size(291, 173);
			this->lsbPartyPokemon->TabIndex = 1;
			// 
			// gbBox
			// 
			this->gbBox->Controls->Add(this->lsbPCPokemon);
			this->gbBox->Controls->Add(this->numCurBox);
			this->gbBox->Location = System::Drawing::Point(321, 50);
			this->gbBox->Name = L"gbBox";
			this->gbBox->Size = System::Drawing::Size(236, 203);
			this->gbBox->TabIndex = 2;
			this->gbBox->TabStop = false;
			this->gbBox->Text = L"PC Box";
			// 
			// lsbPCPokemon
			// 
			this->lsbPCPokemon->FormattingEnabled = true;
			this->lsbPCPokemon->Location = System::Drawing::Point(6, 45);
			this->lsbPCPokemon->Name = L"lsbPCPokemon";
			this->lsbPCPokemon->Size = System::Drawing::Size(224, 147);
			this->lsbPCPokemon->TabIndex = 2;
			// 
			// numCurBox
			// 
			this->numCurBox->Location = System::Drawing::Point(6, 19);
			this->numCurBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 12, 0, 0, 0 });
			this->numCurBox->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numCurBox->Name = L"numCurBox";
			this->numCurBox->Size = System::Drawing::Size(40, 20);
			this->numCurBox->TabIndex = 0;
			this->numCurBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numCurBox->ValueChanged += gcnew System::EventHandler(this, &MainForm::numCurBox_ValueChanged);
			// 
			// gpBackpack
			// 
			this->gpBackpack->Controls->Add(this->lsbBackpack);
			this->gpBackpack->Location = System::Drawing::Point(563, 60);
			this->gpBackpack->Name = L"gpBackpack";
			this->gpBackpack->Size = System::Drawing::Size(229, 193);
			this->gpBackpack->TabIndex = 3;
			this->gpBackpack->TabStop = false;
			this->gpBackpack->Text = L"Backpack";
			// 
			// lsbBackpack
			// 
			this->lsbBackpack->FormattingEnabled = true;
			this->lsbBackpack->Location = System::Drawing::Point(6, 19);
			this->lsbBackpack->Name = L"lsbBackpack";
			this->lsbBackpack->Size = System::Drawing::Size(217, 160);
			this->lsbBackpack->TabIndex = 0;
			// 
			// gpItemBox
			// 
			this->gpItemBox->Controls->Add(this->lsbItemBox);
			this->gpItemBox->Location = System::Drawing::Point(12, 259);
			this->gpItemBox->Name = L"gpItemBox";
			this->gpItemBox->Size = System::Drawing::Size(200, 185);
			this->gpItemBox->TabIndex = 4;
			this->gpItemBox->TabStop = false;
			this->gpItemBox->Text = L"Item Box";
			// 
			// lsbItemBox
			// 
			this->lsbItemBox->FormattingEnabled = true;
			this->lsbItemBox->Location = System::Drawing::Point(6, 19);
			this->lsbItemBox->Name = L"lsbItemBox";
			this->lsbItemBox->Size = System::Drawing::Size(188, 160);
			this->lsbItemBox->TabIndex = 5;
			// 
			// gbTrainerInfo
			// 
			this->gbTrainerInfo->Controls->Add(this->lblLeagueBeat);
			this->gbTrainerInfo->Controls->Add(this->lblPlaytime);
			this->gbTrainerInfo->Controls->Add(this->lblPlrId);
			this->gbTrainerInfo->Controls->Add(this->lblPlrStarter);
			this->gbTrainerInfo->Controls->Add(this->lblCoins);
			this->gbTrainerInfo->Controls->Add(this->lblMoney);
			this->gbTrainerInfo->Controls->Add(this->lblName);
			this->gbTrainerInfo->Location = System::Drawing::Point(218, 259);
			this->gbTrainerInfo->Name = L"gbTrainerInfo";
			this->gbTrainerInfo->Size = System::Drawing::Size(219, 185);
			this->gbTrainerInfo->TabIndex = 5;
			this->gbTrainerInfo->TabStop = false;
			this->gbTrainerInfo->Text = L"Trainer Info";
			// 
			// lblCoins
			// 
			this->lblCoins->AutoSize = true;
			this->lblCoins->Location = System::Drawing::Point(6, 45);
			this->lblCoins->Name = L"lblCoins";
			this->lblCoins->Size = System::Drawing::Size(36, 13);
			this->lblCoins->TabIndex = 2;
			this->lblCoins->Text = L"Coins:";
			// 
			// lblMoney
			// 
			this->lblMoney->AutoSize = true;
			this->lblMoney->Location = System::Drawing::Point(6, 32);
			this->lblMoney->Name = L"lblMoney";
			this->lblMoney->Size = System::Drawing::Size(42, 13);
			this->lblMoney->TabIndex = 1;
			this->lblMoney->Text = L"Money:";
			// 
			// lblName
			// 
			this->lblName->AutoSize = true;
			this->lblName->Location = System::Drawing::Point(6, 19);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(38, 13);
			this->lblName->TabIndex = 0;
			this->lblName->Text = L"Name:";
			// 
			// gbPokedex
			// 
			this->gbPokedex->Controls->Add(this->lbCaught);
			this->gbPokedex->Controls->Add(this->lbSeen);
			this->gbPokedex->Location = System::Drawing::Point(443, 259);
			this->gbPokedex->Name = L"gbPokedex";
			this->gbPokedex->Size = System::Drawing::Size(349, 314);
			this->gbPokedex->TabIndex = 6;
			this->gbPokedex->TabStop = false;
			this->gbPokedex->Text = L"Pokedex";
			// 
			// lbCaught
			// 
			this->lbCaught->FormattingEnabled = true;
			this->lbCaught->Location = System::Drawing::Point(165, 19);
			this->lbCaught->Name = L"lbCaught";
			this->lbCaught->Size = System::Drawing::Size(178, 290);
			this->lbCaught->TabIndex = 1;
			// 
			// lbSeen
			// 
			this->lbSeen->FormattingEnabled = true;
			this->lbSeen->Location = System::Drawing::Point(6, 19);
			this->lbSeen->Name = L"lbSeen";
			this->lbSeen->Size = System::Drawing::Size(153, 290);
			this->lbSeen->TabIndex = 0;
			// 
			// lblPlrStarter
			// 
			this->lblPlrStarter->AutoSize = true;
			this->lblPlrStarter->Location = System::Drawing::Point(7, 58);
			this->lblPlrStarter->Name = L"lblPlrStarter";
			this->lblPlrStarter->Size = System::Drawing::Size(41, 13);
			this->lblPlrStarter->TabIndex = 3;
			this->lblPlrStarter->Text = L"Starter:";
			// 
			// lblPlrId
			// 
			this->lblPlrId->AutoSize = true;
			this->lblPlrId->Location = System::Drawing::Point(6, 71);
			this->lblPlrId->Name = L"lblPlrId";
			this->lblPlrId->Size = System::Drawing::Size(51, 13);
			this->lblPlrId->TabIndex = 4;
			this->lblPlrId->Text = L"Player Id:";
			// 
			// lblPlaytime
			// 
			this->lblPlaytime->AutoSize = true;
			this->lblPlaytime->Location = System::Drawing::Point(6, 84);
			this->lblPlaytime->Name = L"lblPlaytime";
			this->lblPlaytime->Size = System::Drawing::Size(49, 13);
			this->lblPlaytime->TabIndex = 5;
			this->lblPlaytime->Text = L"Playtime:";
			// 
			// lblLeagueBeat
			// 
			this->lblLeagueBeat->AutoSize = true;
			this->lblLeagueBeat->Location = System::Drawing::Point(6, 97);
			this->lblLeagueBeat->Name = L"lblLeagueBeat";
			this->lblLeagueBeat->Size = System::Drawing::Size(70, 13);
			this->lblLeagueBeat->TabIndex = 6;
			this->lblLeagueBeat->Text = L"League beat:";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(820, 606);
			this->Controls->Add(this->gbPokedex);
			this->Controls->Add(this->gbTrainerInfo);
			this->Controls->Add(this->gpItemBox);
			this->Controls->Add(this->gpBackpack);
			this->Controls->Add(this->gbBox);
			this->Controls->Add(this->gbParty);
			this->Controls->Add(this->btnOpenFile);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->gbParty->ResumeLayout(false);
			this->gbBox->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numCurBox))->EndInit();
			this->gpBackpack->ResumeLayout(false);
			this->gpItemBox->ResumeLayout(false);
			this->gbTrainerInfo->ResumeLayout(false);
			this->gbTrainerInfo->PerformLayout();
			this->gbPokedex->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void btnOpenFile_Click(System::Object^ sender, System::EventArgs^ e) {
		ofdGetFile->ShowDialog();
	}
	private: System::Void getFile_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		SaveReader reader(debugMode, ofdGetFile->FileName);

		// Trainer Info
		std::string trainerName = reader.getPlayerName();
		unsigned int trainerMoney = reader.getTrainerMoney();
		unsigned int trainerCoins = reader.getTrainerCoins();
		unsigned short trainerId = reader.getPlayerId();
		unsigned char trainerStarter = reader.getPlayerStarter();
		lblName->Text = "Name: " + PkmStringConverter::toSystemString(trainerName);
		lblMoney->Text = "Money: " + trainerMoney.ToString();
		lblCoins->Text = "Coins: " + trainerCoins.ToString();
		lblPlrStarter->Text = "Starter: " + PkmStringConverter::toSystemString(PkmStringConverter::getPokemonNameById(trainerStarter));
		lblPlrId->Text = "Player Id: " + trainerId.ToString();
		PlayTime playtime = reader.getPlayTime();
		lblPlaytime->Text = "Playtime: " + PkmStringConverter::toSystemString(playtime.getPlaytimeString(" and "));
		lblLeagueBeat->Text = "League Beat: " + reader.getHallOfFameRecordCount().ToString();


		// Party Pokemon
		PokemonParty trainerParty = reader.getTrainerParty();
		lsbPartyPokemon->Items->Clear();
		for (int i = 0; i < trainerParty.count; i++) {
			std::string toWrite = FormatStr::getCoolPokemon(trainerParty.pokemonList[i], trainerParty.pokemonNicknames[i], trainerParty.otNames[i]);
			lsbPartyPokemon->Items->Add(PkmStringConverter::toSystemString(toWrite));
		}
		
		// Box Pokemon
		updateBox(reader);

		// Backpack
		List backpack = reader.getBackpackItemList();
		printList(backpack, lsbBackpack);

		// Item Box
		List itemBox = reader.getList(0x27E6);
		printList(itemBox, lsbItemBox);

		// Pokedex Seen
		for (unsigned short i = 0; i < 151; i++) {
			lbSeen->Items->Add(PkmStringConverter::toSystemString(FormatStr::getPokemon(i, ": " + FormatStr::boolToSeen(reader.isPokemonSeen(i + 1)))));
		}

		// Pokedex Caught
		for (unsigned short i = 0; i < 151; i++) {
			lbCaught->Items->Add(PkmStringConverter::toSystemString(FormatStr::getPokemon(i, ": " + FormatStr::boolToCaught(reader.isPokemonCaught(i + 1)))));
		}
	}

	private: void printList(List lst, ListBox^ toAddTo) {
		for (int i = 0; i < lst.length; i++) {
			System::String^ toAdd = " - " + lst.items[i].amount.ToString() + " " + PkmStringConverter::toSystemString(PkmStringConverter::getItemName(lst.items[i].index));
			toAddTo->Items->Add(toAdd);
		}

	}

	private: void updateBox(SaveReader reader) {
		if (ofdGetFile->FileName->Length != 0) {
			PokemonBox pkmBox = reader.getPokemonBox((unsigned char)numCurBox->Value);
			lsbPCPokemon->Items->Clear();
			for (unsigned char i = 0; i < pkmBox.count; i++) {
				std::string toWrite = (FormatStr::getCoolPokemon(pkmBox.pokemonList[i], pkmBox.pokemonNicknames[i], pkmBox.otNames[i]));
				lsbPCPokemon->Items->Add(PkmStringConverter::toSystemString(toWrite));
			}
		}
	}

	private: void updateBox() {
		if (ofdGetFile->FileName->Length != 0) {
			SaveReader reader(debugMode, ofdGetFile->FileName);
			PokemonBox pkmBox = reader.getPokemonBox((unsigned char)numCurBox->Value);
			lsbPCPokemon->Items->Clear();
			for (unsigned char i = 0; i < pkmBox.count; i++) {
				std::string toWrite = (FormatStr::getCoolPokemon(pkmBox.pokemonList[i], pkmBox.pokemonNicknames[i], pkmBox.otNames[i]));
				lsbPCPokemon->Items->Add(PkmStringConverter::toSystemString(toWrite));
			}
		}
	}

	private: System::Void numCurBox_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		updateBox();
	}
};
}
