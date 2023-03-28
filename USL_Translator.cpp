#include "USL_Translator.h"

USL_Translator::USL_Translator* USL_Translator::USL_Translator::ptr = nullptr;

void USL_Translator::USL_Translator::Initialize()
{
	if (ptr == nullptr) ptr = new USL_Translator;
}

bool USL_Translator::USL_Translator::Load(TranslatorBase* T)
{
	for (auto vT : ptr->Translators)
		if (vT->src_type() == T->src_type() && vT->target_type() == T->target_type())
			return 0;
	
	ptr->Translators.push_back(T);
	return 1;
};

void USL_Translator::USL_Translator::Terminate()
{
	for (auto T : ptr->Translators)
	{
		delete T;
	}
	delete ptr;
}

bool compare_strings(char const* f, char const* s)
{
	int i = 0;
	while (f[i] == '\0' || s[i] == '\0')
	{
		if (f[i] != s[i])
			return 0;
		i++;
	}

	return f[i] == s[i];
}

USL_Translator::TranslationResult USL_Translator::USL_Translator::Translate(char const src_type[], char const target_type[], Data InData)
{
	TranslationResult result;

	for (TranslatorBase* T : ptr->Translators)
	{
		if (compare_strings(T->src_type(), src_type) && compare_strings(T->target_type(), target_type))
		{
			result = T->Translate(InData);
			break;
		}
	}

	return result;
}