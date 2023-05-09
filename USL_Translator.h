#pragma once
#include <stdint.h>
#include <vector>
#include <string>
#include <functional>

#include <map>

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
		std::vector<uint8_t> data;
		std::vector<std::string> prompt{};
	};
	
	/*
		Function that handle loading libraries and other external files
		Called by sigantures like "using library ?n"
		Have to return content of requested file compiled to USL_BINARY
		If file doesn't exsists, return Data object with nullptr pointer and size = 0

		First argument is type of requested file:
			0 - library
		Second argument is file name
	*/
	using LoadExternalFileCallback = std::function<Data(int, std::string)>;

	/*
		by inheriting from this class, we create new translators
	*/
	class TranslatorBase
	{
	public:
		virtual TranslationResult Translate(Data InData, LoadExternalFileCallback LEFC) = 0;
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
		static TranslationResult Translate
		(char const src_type[], char const target_type[], Data InData, LoadExternalFileCallback LLC);
	};
	
}