#pragma once
#include <stdint.h>
#include <vector>
#include <string>

namespace USL_Translator
{
	struct Data
	{
		void* position = nullptr;
		uint64_t size = 0;
		Data() {};
		Data(void* _position, uint64_t _size) : position(_position), size(_size) {};
	};

	struct TranslationResult
	{
		bool success = false;
		void* data_position = nullptr;
		int data_size = 0;
		std::vector<std::string> prompt{};
	};

	/*
		by inheriting from this class, we create new translators
	*/
	class TranslatorBase
	{
	public:
		virtual TranslationResult Translate(Data InData) = 0;
		virtual const char* src_type() = 0;
		virtual const char* target_type() = 0;
	private:
	};

	class USL_Translator 
	{
	protected:
		//Singletone
		USL_Translator(){};
		std::vector<TranslatorBase*> Translators;
		static USL_Translator* ptr;

	public:
		//Delete copies
		USL_Translator(USL_Translator& other) = delete;
		void operator=(const USL_Translator&) = delete;

		static void Initialize();
		//User have to provide pointer to translator. This version of load will be used in non - standalone compiler, build in for example an game
		static bool Load(TranslatorBase* T);
		static void Terminate();
		static TranslationResult Translate(char const src_type[], char const target_type[], Data Data);
	};
	
}