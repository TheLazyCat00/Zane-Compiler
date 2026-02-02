#include <algorithm>
#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "utils/print.hpp"

namespace repl {

struct ReplResult {
	std::map<std::string, std::any> result;
};

enum QuestionStatus {
	Success,
	Error,
};

struct Question {
	virtual QuestionStatus askQuestion(ReplResult& result, const std::string& input) const = 0;
	virtual std::string getPrompt() const = 0;  // <--- new
	virtual ~Question() = default;

	std::string name;
};

struct OpenQuestion : Question {
	QuestionStatus askQuestion(ReplResult& result, const std::string& input) const override {
		result.result[name] = input;
		return Success;
	}

	std::string getPrompt() const override { return prompt; }

	std::string prompt;

	OpenQuestion(std::string name, std::string prompt) {
		this->name = name;
		this->prompt = prompt;
	}
};

template<typename T>
struct ChoiceQuestion : Question {
	QuestionStatus askQuestion(ReplResult& result, const std::string& input) const override {
		auto it = choices.find(input);
		if (it != choices.end()) {
			result.result[name] = it->second;
			return Success;
		} else {
			return Error;
		}
	}

	std::string getPrompt() const override { return prompt; }

	std::string prompt;
	std::map<std::string, T> choices;

	ChoiceQuestion(std::string n, std::string p, std::map<std::string, T> c) {
		name = n;
		prompt = p;
		choices = c;
	}
};

struct Repl {
	std::string startMsg;
	std::vector<std::unique_ptr<Question>> questions;

	ReplResult open() {
		ReplResult result;
		std::string input;

		print(startMsg);

		for (size_t i = 0; i < questions.size(); ) {
			print(questions[i]->getPrompt());
			std::getline(std::cin, input);
			std::transform(input.begin(), input.end(), input.begin(), ::tolower);

			auto status = questions[i]->askQuestion(result, input);
			if (status == Success) {
				++i;
			} else {
				print("Input not accepted");
			}
		}

		return result;
	}
};

}
