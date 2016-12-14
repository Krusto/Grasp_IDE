#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "DrawingFunctions.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <sstream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <regex>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <sys/types.h>
#include <io.h>
#include <Tlhelp32.h>
#include <winbase.h>

short StartPointY = 150;
short StartPointX = 590;

cv::Point MouseCoords;
cv::Point MouseMovementCoords;

class keyWord {
public:
	int id;
	int x;
	short width;
	std::string value;
	int lineNumber;
	RGBcolor keyWordColor = RGBcolor(255, 255, 255);
	short allWidth;
	keyWord() {}
	keyWord(int id, int x, int lineNumber, short width, std::string value) {
		this->id = id;
		this->x = x;
		this->lineNumber = lineNumber;
		this->width = width;
		this->value = value;
	}
	keyWord(int id, int x, int lineNumber, short width, std::string value, short allWidth) {
		this->id = id;
		this->x = x;
		this->lineNumber = lineNumber;
		this->width = width;
		this->allWidth = allWidth;
		this->value = value;
	}
	keyWord(int id, int x, int lineNumber, short width, std::string value, RGBcolor KeyWordColor) {
		this->id = id;
		this->x = x;
		this->keyWordColor = KeyWordColor;
		this->lineNumber = lineNumber;
		this->width = width;
		this->value = value;
	}
};
std::vector<keyWord> insertElement(std::vector<keyWord>Keys, keyWord Key) {
	Keys.insert(Keys.begin() + Key.id, keyWord(Key.id, Keys[Key.id].x, Keys[Key.id].lineNumber, Key.width, Key.value));
	for (short j = Key.id + 1; j < Keys.size(); j++) {
		Keys.at(j) = keyWord(Keys.at(j).id + 1, Keys.at(j - 1).x + Keys.at(j - 1).width, Keys.at(j).lineNumber, Keys.at(j).width, Keys.at(j).value);
	}
	return Keys;
}
std::vector<keyWord>eraseElement(std::vector<keyWord>Keys, keyWord Key) {
	for (short i = Key.id; i < Keys.size(); i++) {
		if (i + 1 < Keys.size()) {
			Keys.at(i).value = Keys.at(i + 1).value;
			Keys.at(i).width = Keys.at(i + 1).width;
			if (i - 1 > 0)
				Keys.at(i).x = Keys.at(i - 1).x + Keys.at(i - 1).width;
		}
		else if (Key.id == 0) {
			Keys.at(0).id = Keys.at(1).id;
			Keys.at(0).value = Keys.at(1).value;
			Keys.at(0).width = Keys.at(1).width;
		}
	}
	for (short i = 0; i < Keys.size(); i++) {
		Keys.at(i).id = i;
	}
	Keys.erase(Keys.end() - 1);
	return Keys;
}
int keyPressed(int key) {
	return (GetAsyncKeyState(key) & 0x8000 != 0);
}
bool leftMouseKeyPressed() {
	if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

/*std::vector<keyWord> syntax(std::vector<keyWord>Keys, std::vector<std::string>Words, std::vector<RGBcolor> color, std::string windowName, WindowDraw canvas, bool isActiveRenderNormalWords = true) {
	Canvas::Draw window = Canvas::Draw();
	bool allDone = NULL;
	short SyntaxWordsPosition = 0;
	short KeysPosition = 0;
	for (KeysPosition = 0; KeysPosition < Keys.size(); KeysPosition++) {
		allDone = NULL;
		if (Keys.at(KeysPosition).value != "\n") {

			for (SyntaxWordsPosition = 0; SyntaxWordsPosition < Words.size(); SyntaxWordsPosition++) {
				if (Keys.size() > Words.at(SyntaxWordsPosition).size() && KeysPosition + Words.at(SyntaxWordsPosition).size() < Keys.size()) {
					short i = 0;
					while (i < Words.at(SyntaxWordsPosition).size()) {
						std::string nowWordString = Words.at(SyntaxWordsPosition);
						std::stringstream nowWordStream;
						nowWordStream << nowWordString.at(i);
						std::string nowWordChar2String;
						nowWordStream >> nowWordChar2String;
						if (Keys.at(KeysPosition + i).value == nowWordChar2String) {
							allDone = true;
							i++;
						}
						else {
							allDone = false;
							i = Words.at(SyntaxWordsPosition).size();
						}
					}
					i = 0;
					if (allDone == true) {
						while (i < Words.at(SyntaxWordsPosition).size()) {
							if (SyntaxWordsPosition + i < 65) {
								if (KeysPosition != 0) {
									Keys.at(KeysPosition + i - 1).keyWordColor = color.at(0);
								}
								Keys.at(KeysPosition + i).keyWordColor = color.at(0);
								putText(canvas, Keys.at(KeysPosition + i).value, cv::Point(Keys.at(KeysPosition + i).x, StartPointY + (Keys.at(KeysPosition + i).lineNumber * 20)), 0, 0.6, cvScalar(color.at(0).red, color.at(0).green, color.at(0).blue), 0, CV_AA);

							}
							if (SyntaxWordsPosition + i > 64 && SyntaxWordsPosition + i < 65 + 17) {
								if (KeysPosition != 0) {
									Keys.at(KeysPosition + i - 1).keyWordColor = color.at(1);
								}
								Keys.at(KeysPosition + i).keyWordColor = color.at(1);
								window.drawFillRect(Keys.at(KeysPosition + i).x - 1, StartPointY + (Keys.at(KeysPosition + i).lineNumber * 23) - 22, Keys.at(KeysPosition + i).width + 2, 25, 30, 30, 30, windowName, canvas);
								putText(canvas, Keys.at(KeysPosition + i).value, cv::Point(Keys.at(KeysPosition + i).x, StartPointY + (Keys.at(KeysPosition + i).lineNumber * 20)), 0, 0.6, cvScalar(color.at(1).red, color.at(1).green, color.at(1).blue), 0, CV_AA);

							}
							if (SyntaxWordsPosition + i > 65 + 16) {
								Keys[NumberLines][Keys[NumberLines].size() - 1] << "bla";
								if (KeysPosition != 0) {
									Keys.at(KeysPosition + i - 1).keyWordColor = color.at(2);
								}
								Keys.at(KeysPosition + i).keyWordColor = color.at(2);
								putText(canvas, Keys.at(KeysPosition + i).value, cv::Point(Keys.at(KeysPosition + i).x, StartPointY + (Keys.at(KeysPosition + i).lineNumber * 20)), 0, 0.6, cvScalar(color.at(2).red, color.at(2).green, color.at(2).blue), 0, CV_AA);
							}
							i++;
						}
						SyntaxWordsPosition = Words.size();
						KeysPosition += i;
					}
					else {
						if (allDone == false && isActiveRenderNormalWords == true) {
							putText(canvas, Keys.at(KeysPosition).value, cv::Point(Keys.at(KeysPosition).x, StartPointY + (Keys.at(KeysPosition).lineNumber * 20)), 0, 0.6, cvScalar(255, 255, 255), 0, CV_AA);
						}
					}
				}
			}
			putText(canvas, Keys.at(KeysPosition).value, cv::Point(Keys.at(KeysPosition).x, StartPointY + (Keys.at(KeysPosition).lineNumber * 20)), 0, 0.6, cvScalar(255, 255, 255), 0, CV_AA);

		}
	}
	return Keys;
}*/
std::string getFileNameOfPath(std::string path) {
	std::string filePath = path;
	int i = filePath.find_last_of("\\");
	if (i != std::string::npos) {
		filePath = filePath.substr(i + 1);
	}
	return filePath;
}
std::string keyWordVectorToString(std::vector<keyWord>Keys) {
	std::string sentence;
	for (int x = 0; x < Keys.size(); x++) {
		sentence += Keys.at(x).value;
	}
	return sentence;
}
void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == cv::EVENT_MOUSEMOVE) {
		MouseMovementCoords.x = x;
		MouseMovementCoords.y = y;
	}
	MouseCoords.x = x;
	MouseCoords.y = y;
}
void killProcessByName(const char *filename)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (strcmp(pEntry.szExeFile, filename) == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}
int main() {

	int windowSizeW = 1920, windowSizeH = 1080;
	WindowDraw canvas(cv::Size(windowSizeW, windowSizeH), CV_8UC3);

	Canvas::Draw window = Canvas::Draw();
	Canvas::OtherFunctions functions = Canvas::OtherFunctions();

	std::string windowName = "Grasp";
	window.CreateWindowe(windowName, 0, 0, windowSizeW, windowSizeH, COLOR_SCALE::RGB, canvas);

	std::vector<std::vector<keyWord>> Keys;

	short NumberLines = 0;
	int CurrentLine = 0;
	int ElementIDOnThatLine = 0;
	char KeyPressed_CHAR;
	std::string KeyPressed_STRING;
	cv::Point EditorMouseCoords;
	bool Exit = false, LeftMouseButtonClicked = 0;
	std::stringstream NumberLinesStream;
	NumberLinesStream << NumberLines;

	std::string FileName = "Untitled";
	bool IsFileSaved = true;
	std::string FileNamePath = "";
	int KeyPressed_INT;


	//navigation bar
	window.drawFillRect(0, 0, windowSizeW, 40, 77, 77, 79, windowName, canvas);
	//background
	window.drawFillRect(0, 40, windowSizeW, windowSizeH - 40, 45, 45, 48, windowName, canvas);
	//file manager
	window.drawFillRect(0, 110, 500, windowSizeH - 110, 30, 30, 30, windowName, canvas);
	//editor
	window.drawFillRect(520, 130, 1392, 675, 77, 77, 79, windowName, canvas);
	//editor box
	window.drawFillRect(580, 130, 1312, 650, 30, 30, 30, windowName, canvas);
	//scroll bar vertical
	window.drawFillRect(1893, 130, 20, 290, 126, 126, 126, windowName, canvas);
	//build log dark
	window.drawFillRect(520, 820, 1392, 260, 30, 30, 30, windowName, canvas);
	//build log light
	window.drawFillRect(520, 820, 1392, 25, 77, 77, 77, windowName, canvas);
	//new file box
	window.drawImage("Assets/Icons/NewFile.jpg", 10, 59, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/OpenFile.jpg", 135, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/BuildAndRun.jpg", 260, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/Build.jpg", 454, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/Run.jpg", 547, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/Undo.jpg", 623, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/Redo.jpg", 730, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/Search.jpg", 836, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/Replace.jpg", 937, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/Save.jpg", 1057, 60, 77, 77, 79, COLOR_SCALE::RGB, windowName, canvas);

	window.drawText(540, 838, "Build Messages", 255, 255, 255, 0.6, windowName, canvas);

	window.drawImage("Assets/TopLine/File.jpg", 0, 0, 79, 79, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/TopLine/Edit.jpg", 74, 0, 79, 79, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/TopLine/Search.jpg", 148, 0, 79, 79, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/TopLine/Build.jpg", 250, 0, 79, 79, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/TopLine/Settings.jpg", 339, 0, 79, 79, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/TopLine/Help.jpg", 462, 0, 79, 79, 79, COLOR_SCALE::RGB, windowName, canvas);
	window.drawImage("Assets/Icons/hix.jpg", windowSizeW - 43, 6, 25, 25, 77, 77, 79, COLOR_SCALE::RGB, true, windowName, canvas);
	window.drawText(545, 154, "1", 255, 255, 255, 0.6, windowName, canvas);
	Keys.push_back(std::vector<keyWord>{keyWord(0, StartPointX, 0, 0, "", StartPointX)});
	short nowRunningCodeNumWindows = 0;
	while (Exit == false) {

		LeftMouseButtonClicked = 0;

		cv::setMouseCallback(windowName, onMouse);
		LeftMouseButtonClicked = leftMouseKeyPressed();

		KeyPressed_CHAR = cv::waitKey(1);
		KeyPressed_INT = KeyPressed_CHAR;
		KeyPressed_STRING = KeyPressed_CHAR;

		window.drawFillRect(580, 130, 1312, 650, 30, 30, 30, windowName, canvas);
		window.drawFillRect(Keys[CurrentLine][ElementIDOnThatLine].x + Keys[CurrentLine][ElementIDOnThatLine].width, StartPointY + (Keys[CurrentLine][ElementIDOnThatLine].lineNumber * 25) - 15, 1, 20, 255, 255, 255, windowName, canvas);
		window.drawText(545, 154, "1", 255, 255, 255, 0.6, windowName, canvas);

		window.drawFillRect(1164, 100, getFileNameOfPath(FileName).length() * 12, 27, 77, 77, +79, windowName, canvas);
		window.drawText(1176, 120, getFileNameOfPath(FileName), 255, 255, 255, 0.5, windowName, canvas);

		for (int i = 0; i < Keys.size(); i++) {
			for (int j = 0; j < Keys.at(i).size(); j++) {
				if (Keys[i][j].value != "\n" && Keys[i][j].value != "") {
					putText(canvas, Keys[i][j].value, cv::Point(Keys[i][j].x, StartPointY + (Keys[i][j].lineNumber * 25)), 0, 0.6, cvScalar(255, 255, 255), 0, CV_AA);
				}
			}
		}
		for (short i = 0; i < NumberLines; i++) {
			putText(canvas, std::to_string(i + 2), cv::Point(545, StartPointY + (25 * i) + 25), 0, 0.6, cvScalar(255, 255, 255), 0, CV_AA);
		}

		if (KeyPressed_INT == -1) {
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			if (IsFileSaved == true) {
				IsFileSaved = false;
				FileName.append("*");
			}
			if (ElementIDOnThatLine - 1 >= 0) {
				ElementIDOnThatLine--;
			}
			else
				if (ElementIDOnThatLine == 0 && CurrentLine - 1 >= 0) {
					CurrentLine--;
					ElementIDOnThatLine = Keys[CurrentLine].size() - 1;
				}
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			if (IsFileSaved == true) {
				IsFileSaved = false;
				FileName.append("*");
			}
			if (ElementIDOnThatLine + 1 <= Keys[CurrentLine][Keys[CurrentLine].size() - 1].id) {
				ElementIDOnThatLine++;
			}
			else if (ElementIDOnThatLine == Keys[CurrentLine][Keys[CurrentLine].size() - 1].id && CurrentLine + 1 <= NumberLines) {
				CurrentLine++;
				ElementIDOnThatLine = 0;
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			if (IsFileSaved == true) {
				IsFileSaved = false;
				FileName.append("*");
			}
			if (CurrentLine - 1 >= 0) {
				if (Keys[CurrentLine - 1].size() - 1 < ElementIDOnThatLine) {
					ElementIDOnThatLine = Keys[CurrentLine - 1].size() - 1;
				}
				CurrentLine--;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			if (IsFileSaved == true) {
				IsFileSaved = false;
				FileName.append("*");
			}
			if (CurrentLine + 1 <= NumberLines) {
				if (ElementIDOnThatLine > Keys[CurrentLine + 1].size() - 1) {
					ElementIDOnThatLine = Keys[CurrentLine + 1].size() - 1;
				}
				CurrentLine++;
			}
		}
		else if (KeyPressed_INT == 8) {
			if (IsFileSaved == true) {
				IsFileSaved = false;
				FileName.append("*");
			}
			if (ElementIDOnThatLine - 1 < 0 && CurrentLine < NumberLines && CurrentLine - 1 >= 0 && Keys[CurrentLine].size() - 1 == 0) {
				CurrentLine--;
				NumberLines--;
				ElementIDOnThatLine = Keys[CurrentLine].size() - 1;

				for (short i = CurrentLine + 1; i < Keys.size(); i++) {
					for (short j = 0; j < Keys[i].size(); j++) {
						Keys[i][j].lineNumber = Keys[i][j].lineNumber - 1;
					}
				}
				Keys.erase(Keys.begin() + CurrentLine + 1);
				window.drawFillRect(525, 130, 50, 650, 77, 77, 79, windowName, canvas);

			}
			else if (ElementIDOnThatLine - 1 < 0 && CurrentLine < NumberLines && CurrentLine - 1 >= 0 && Keys[CurrentLine].size() - 1 != 0) {

			}
			else if (ElementIDOnThatLine - 1 >= 0) {
				Keys[CurrentLine] = eraseElement(Keys[CurrentLine], Keys[CurrentLine][ElementIDOnThatLine]);
				ElementIDOnThatLine--;
			}
			else if (ElementIDOnThatLine == 0 && CurrentLine - 1 >= 0) {
				Keys.erase(Keys.begin() + CurrentLine);
				NumberLines--;
				CurrentLine--;
				ElementIDOnThatLine = Keys[CurrentLine].size() - 1;
				window.drawFillRect(525, 130, 50, 650, 77, 77, 79, windowName, canvas);
			}
		}
		else if (KeyPressed_INT == 13) {
			if (IsFileSaved == true) {
				IsFileSaved = false;
				FileName.append("*");
			}
			if (NumberLines + 1 <= 25) {
				CurrentLine++;
				NumberLines++;
				ElementIDOnThatLine = 0;

				if (CurrentLine < NumberLines) {
					Keys.insert(Keys.begin() + CurrentLine, std::vector<keyWord>{keyWord(0, StartPointX, CurrentLine, 0, "\n", StartPointX)});
					window.drawFillRect(Keys[CurrentLine][ElementIDOnThatLine].x + Keys[CurrentLine][ElementIDOnThatLine].width, StartPointY + (Keys[CurrentLine][ElementIDOnThatLine].lineNumber * 25) - 15, 1, 20, 255, 255, 255, windowName, canvas);
					for (short i = CurrentLine + 1; i < Keys.size(); i++) {
						for (short j = 0; j < Keys[i].size(); j++) {
							Keys[i][j].lineNumber = Keys[i][j].lineNumber + 1;
						}
					}
				}
				else {
					Keys.push_back(std::vector<keyWord>{keyWord(0, StartPointX, CurrentLine, 0, "\n", StartPointX)});
					window.drawFillRect(Keys[CurrentLine][ElementIDOnThatLine].x + Keys[CurrentLine][ElementIDOnThatLine].width, StartPointY + (Keys[CurrentLine][ElementIDOnThatLine].lineNumber * 25) - 15, 1, 20, 255, 255, 255, windowName, canvas);
				}
			}
		}
		else {
			if (IsFileSaved == true) {
				FileName.append("*");
				IsFileSaved = false;
			}
			window.drawFillRect(Keys[CurrentLine][Keys[CurrentLine].size() - 1 - ElementIDOnThatLine].x + Keys[CurrentLine][Keys[CurrentLine].size() - 1 - ElementIDOnThatLine].width, StartPointY + (Keys[CurrentLine][Keys[CurrentLine].size() - 1 - ElementIDOnThatLine].lineNumber * 25) - 15, 1, 20, 30, 30, 30, windowName, canvas);
			if (ElementIDOnThatLine < Keys[CurrentLine][Keys[CurrentLine].size() - 1].id) {
				if (KeyPressed_CHAR == 'm' || KeyPressed_CHAR == '^' || KeyPressed_CHAR == 'W' || KeyPressed_CHAR == '=') {
					Keys.at(CurrentLine) = insertElement(Keys[CurrentLine], keyWord(Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine), Keys[CurrentLine][Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine)].x, CurrentLine, 23, KeyPressed_STRING));
				}
				else if (KeyPressed_CHAR == 'r' || KeyPressed_CHAR == 't' || KeyPressed_CHAR == 'j' || KeyPressed_CHAR == 'i' || KeyPressed_CHAR == 'f' || KeyPressed_CHAR == 'l' || KeyPressed_CHAR == '!' || KeyPressed_CHAR == ':' || KeyPressed_CHAR == '.') {
					Keys.at(CurrentLine) = insertElement(Keys[CurrentLine], keyWord(Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine), Keys[CurrentLine][Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine)].x, CurrentLine, 11, KeyPressed_STRING));
				}
				else if (KeyPressed_CHAR == 'y') {
					Keys.at(CurrentLine) = insertElement(Keys[CurrentLine], keyWord(Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine), Keys[CurrentLine][Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine)].x, CurrentLine, 12, KeyPressed_STRING));
				}
				else if (KeyPressed_CHAR == 'w' || KeyPressed_CHAR == 'M') {
					Keys.at(CurrentLine) = insertElement(Keys[CurrentLine], keyWord(Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine), Keys[CurrentLine][Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine)].x, CurrentLine, 15, KeyPressed_STRING));
				}
				else if (KeyPressed_CHAR == '@' || KeyPressed_CHAR == '%' || KeyPressed_CHAR == '&' || KeyPressed_CHAR == '+' || KeyPressed_CHAR == '<' || KeyPressed_CHAR == '>') {
					Keys.at(CurrentLine) = insertElement(Keys[CurrentLine], keyWord(Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine), Keys[CurrentLine][Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine)].x, CurrentLine, 19, KeyPressed_STRING));
				}
				else {
					Keys.at(CurrentLine) = insertElement(Keys[CurrentLine], keyWord(Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine), Keys[CurrentLine][Keys.at(CurrentLine).size() - (Keys[CurrentLine][Keys[CurrentLine].size() - 1].id - ElementIDOnThatLine)].x, CurrentLine, 14, KeyPressed_STRING));
				}
				Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].x, CurrentLine, 0, "", Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth));

				ElementIDOnThatLine++;
			}
			else {
				ElementIDOnThatLine++;
				if (KeyPressed_CHAR == 'm' || KeyPressed_CHAR == '^' || KeyPressed_CHAR == 'W' || KeyPressed_CHAR == '=') {
					Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 23, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 21));
				}
				else if (KeyPressed_CHAR == 'r' || KeyPressed_CHAR == 't' || KeyPressed_CHAR == 'j' || KeyPressed_CHAR == 'i' || KeyPressed_CHAR == 'f' || KeyPressed_CHAR == 'l' || KeyPressed_CHAR == '!' || KeyPressed_CHAR == ':' || KeyPressed_CHAR == '.') {
					Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 11, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 9));
				}
				else if (KeyPressed_CHAR == 'y') {
					Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 12, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 10));
				}
				else if (KeyPressed_CHAR == 'w' || KeyPressed_CHAR == 'M') {
					Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 15, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 13));
				}
				else if (KeyPressed_CHAR == '@' || KeyPressed_CHAR == '%' || KeyPressed_CHAR == '&' || KeyPressed_CHAR == '+' || KeyPressed_CHAR == '<' || KeyPressed_CHAR == '>') {
					Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 19, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 17));
				}
				else {
					Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 14, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 15));
				}
			}
		}

		if (MouseMovementCoords.x >= 1057 && MouseMovementCoords.x < 1057 + 81 && MouseMovementCoords.y >= 57 && MouseMovementCoords.y < 94 && LeftMouseButtonClicked == true) {
			if (getFileNameOfPath(FileName) != "Untitled") {
				if (FileName.at(FileName.size() - 1) == '*') {
					FileName.erase(FileName.end() - 1);
				}
				std::ofstream file(FileNamePath);
				for (int i = 0; i < Keys.size(); i++) {
					for (int j = 0; j < Keys[i].size(); j++) {
						file << Keys[i][j].value;
					}
				}
				file.close();

				window.drawFillRect(1164, 100, getFileNameOfPath(FileName).length() * 12, 27, 77, 77, +79, windowName, canvas);
				window.drawText(1176, 120, getFileNameOfPath(FileName), 255, 255, 255, 0.5, windowName, canvas);
				if (IsFileSaved == false) {
					IsFileSaved = true;
				}
			}
		}
		if (MouseMovementCoords.x >= 454 && MouseMovementCoords.x < 542 && MouseMovementCoords.y >= 57 && MouseMovementCoords.y < 94 && LeftMouseButtonClicked == true) {
			std::ifstream ProgramInfo("Grasp.conf");
			std::string GraspPath;
			if (getFileNameOfPath(FileName) != "Untitled") {
				std::ofstream file(FileNamePath);

				std::getline(ProgramInfo, GraspPath);

				const char* Command;
				std::string CommandStr = GraspPath + "\\MinGW\\bin\\g++.exe " + FileNamePath + " -o " + FileNamePath + ".exe";
				for (int i = 0; i < Keys.size(); i++) {
					for (int j = 0; j < Keys[i].size(); j++) {
						file << Keys[i][j].value;
					}
				}
				file.close();
				Command = CommandStr.c_str();
				system(Command);
			}
		}
		if (MouseMovementCoords.x >= 547 && MouseMovementCoords.x < 618 && MouseMovementCoords.y >= 57 && MouseMovementCoords.y < 94 && LeftMouseButtonClicked == true) {
			if (getFileNameOfPath(FileName) != "Untitled") {
				std::ifstream ProgramInfo("Grasp.conf");
				std::string GraspPath;
				std::getline(ProgramInfo, GraspPath);

				const char* Command;

				std::string CommandStr = "\"" + FileNamePath;

				for (int i = 0; i < CommandStr.length(); i++) {
					if (CommandStr.at(i) == '\\') {
						CommandStr.insert(i, "\\");
						i++;
					}
				}
				CommandStr.append(".exe\"");
				Command = CommandStr.c_str();

				const char* FilePath;
				FilePath = FileNamePath.c_str() + '.exe';
				nowRunningCodeNumWindows++;
				ShellExecute(GetDesktopWindow(), "open", Command, NULL, NULL, SW_SHOWNORMAL);
			}
			cv::waitKey(100);
		}
		if (MouseMovementCoords.x >= 10 && MouseMovementCoords.x < 141 && MouseMovementCoords.y >= 60 && MouseMovementCoords.y < 60 + 32 && LeftMouseButtonClicked == true) {
			std::vector<keyWord> FilePath;

			StartPointX = windowSizeW / 2 - 250 + 5;
			StartPointY = windowSizeH / 2 + 3;
			LeftMouseButtonClicked = 0;
			bool IsOkay = false;
			bool IsEnterPressed = false;
			bool fileExist = true;
			bool fileExistEnterPressed = false;
			FilePath.push_back(keyWord(0, StartPointX, 1, 0, "", StartPointX));

			while (IsOkay == false) {

				KeyPressed_CHAR = cv::waitKey(1);
				KeyPressed_INT = KeyPressed_CHAR;
				cv::setMouseCallback(windowName, onMouse);
				LeftMouseButtonClicked = leftMouseKeyPressed();

				window.drawFillRect(windowSizeW / 2 - 300, windowSizeH / 2 - 100, 600, 170, 77, 77, 79, windowName, canvas);
				window.drawStrokeRect(windowSizeW / 2 - 300, windowSizeH / 2 - 100, 600, 170, 0, 0, 0, windowName, canvas);
				window.drawFillRect(windowSizeW / 2 - 250, windowSizeH / 2 - 20, 460, 33, 127, 125, 127, windowName, canvas);
				window.drawText(windowSizeW / 2 - 248, windowSizeH / 2 - 35, "File path", 255, 255, 255, 0.8, windowName, canvas);

				window.drawImage("Assets/Icons/hix.jpg", windowSizeW / 2 + 250, windowSizeH / 2 - 90, 32, 32, 77, 77, 79, COLOR_SCALE::RGB, true, windowName, canvas);

				window.drawFillRect(windowSizeW / 2 - 250 + 470, windowSizeH / 2 - 20, 75, 34, 100, 100, 100, windowName, canvas);
				window.drawText(windowSizeW / 2 + 233 - 5, windowSizeH / 2 + 3, "Create", 255, 255, 255, 0.6, windowName, canvas);

				window.drawFillRect(FilePath.at(FilePath.size() - 1).x + FilePath.at(FilePath.size() - 1).width, StartPointY - 15, 1, 20, 255, 255, 255, windowName, canvas);

				for (short i = 0; i < FilePath.size(); i++) {
					putText(canvas, FilePath.at(i).value, cv::Point(FilePath.at(i).x, StartPointY), 0, 0.6, cvScalar(255, 255, 255), 0, CV_AA);
				}

				if (MouseMovementCoords.x >= windowSizeW / 2 + 250 && MouseMovementCoords.x < windowSizeW / 2 + 250 + 32 && MouseMovementCoords.y >= windowSizeH / 2 - 90 && MouseMovementCoords.y < windowSizeH / 2 - 90 + 32 && LeftMouseButtonClicked == true) {
					IsOkay = true;
					StartPointX = 590;
					StartPointY = 150;
					window.drawFillRect(windowSizeW / 2 - 300, windowSizeH / 2 - 100, 600, 170, 30, 30, 30, windowName, canvas);
				}

				if (MouseMovementCoords.x >= windowSizeW / 2 - 250 + 470 && MouseMovementCoords.x < windowSizeW / 2 - 250 + 470 + 75 && MouseMovementCoords.y >= windowSizeH / 2 - 20 && MouseMovementCoords.y < windowSizeH / 2 - 20 + 34 && LeftMouseButtonClicked == true || IsEnterPressed == true) {


					std::string FileFullPath = keyWordVectorToString(FilePath);
					if (FileFullPath.length() > 1) {
						if (std::ifstream(FileFullPath)) {
							fileExist = true;
						}
						else {
							FileName = getFileNameOfPath(FileFullPath);
							FileNamePath = FileFullPath;

							window.drawFillRect(580, 130, 1312, 650, 30, 30, 30, windowName, canvas);
							window.drawFillRect(windowSizeW / 2 - 300, windowSizeH / 2 - 100, 600, 170, 30, 30, 30, windowName, canvas);
							window.drawFillRect(1164, 100, 100, 27, 77, 77, +79, windowName, canvas);
							window.drawText(1176, 120, FileName, 255, 255, 255, 0.5, windowName, canvas);
							std::ofstream file;
							file.open(FileFullPath);
							file.close();
							IsOkay = true;
							Keys.clear();
							Keys.push_back(std::vector<keyWord>{keyWord(0, 590, 0, 0, "", 590)});
							ElementIDOnThatLine = 0;
							NumberLines = 0;
							CurrentLine = 0;
							StartPointX = 590;
							StartPointY = 150;
							fileExist = false;
						}
					}
				}
				if (fileExist == true) {
					window.drawFillRect(windowSizeW / 2 - 250, windowSizeH / 2 + 14, 300, 30, 77, 77, 79, windowName, canvas);
					window.drawText(windowSizeW / 2 - 250, windowSizeH / 2 + 33, "File is existing", 0, 0, 255, 0.6, windowName, canvas);
					IsEnterPressed = false;
				}

				if (KeyPressed_INT == -1) {}
				else if (KeyPressed_INT == 13) {
					IsEnterPressed = true;
				}
				else if (KeyPressed_INT == 8) {
					if (FilePath.size() - 1 != 0) {
						if (FilePath.at(FilePath.size() - 1).value == "") {
							FilePath.erase(FilePath.end() - 1);
						}
						else {
							FilePath.erase(FilePath.end() - 1);
						}
					}
				}
				else {
					window.drawFillRect(FilePath.at(FilePath.size() - 1).x + FilePath.at(FilePath.size() - 1).width, StartPointY - 20, 1, 20, 128, 128, 127, windowName, canvas);
					KeyPressed_STRING = KeyPressed_CHAR;
					if (KeyPressed_CHAR == 'm' || KeyPressed_CHAR == '^' || KeyPressed_CHAR == 'W' || KeyPressed_CHAR == '=') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 18, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 15));
					}
					else if (KeyPressed_CHAR == 'r' || KeyPressed_CHAR == 't' || KeyPressed_CHAR == 'j') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 8, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 5));
					}
					else if (KeyPressed_CHAR == 'i' || KeyPressed_CHAR == 'f' || KeyPressed_CHAR == 'l' || KeyPressed_CHAR == '!' || KeyPressed_CHAR == ':' || KeyPressed_CHAR == '.') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 6, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 6));
					}
					else if (KeyPressed_CHAR == 'y') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 10, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 7));
					}
					else if (KeyPressed_CHAR == 'w' || KeyPressed_CHAR == 'M') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth - 1, 1, 13, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 10));
					}
					else if (KeyPressed_CHAR == '@' || KeyPressed_CHAR == '%' || KeyPressed_CHAR == '&' || KeyPressed_CHAR == '+' || KeyPressed_CHAR == '<' || KeyPressed_CHAR == '>') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 17, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 14));
					}
					else {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 12, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 12));
					}
				}

				cv::imshow(windowName, canvas);
			}
		}
		if (MouseMovementCoords.x >= 260 && MouseMovementCoords.x < 260 + 189 && MouseMovementCoords.y>57 && MouseMovementCoords.y < 94 && LeftMouseButtonClicked == true) {
			if (getFileNameOfPath(FileName) != "Untitled") {
				std::ifstream ProgramInfo("Grasp.conf");
				std::string GraspPath;
				std::getline(ProgramInfo, GraspPath);
				std::ofstream file(FileNamePath);

				std::getline(ProgramInfo, GraspPath);

				const char* Command;
				std::string CommandStr = GraspPath + "\\MinGW\\bin\\g++.exe " + FileNamePath + " -o " + FileNamePath + ".exe";
				for (int i = 0; i < Keys.size(); i++) {
					for (int j = 0; j < Keys[i].size(); j++) {
						file << Keys[i][j].value;
					}
				}
				file.close();
				Command = CommandStr.c_str();
				system(Command);

				CommandStr = "\"" + FileNamePath;

				for (int i = 0; i < CommandStr.length(); i++) {
					if (CommandStr.at(i) == '\\') {
						CommandStr.insert(i, "\\");
						i++;
					}
				}
				CommandStr.append(".exe\"");
				Command = CommandStr.c_str();

				const char* FilePath;
				FilePath = FileNamePath.c_str() + '.exe';
				ShellExecute(GetDesktopWindow(), "open", Command, NULL, NULL, SW_SHOWNORMAL);
			}
		}
		if (MouseMovementCoords.x >= 135 && MouseMovementCoords.x < 255 && MouseMovementCoords.y>57 && MouseMovementCoords.y < 94 && LeftMouseButtonClicked == true) {
			std::vector<keyWord> FilePath;

			StartPointX = windowSizeW / 2 - 250 + 5;
			StartPointY = windowSizeH / 2 + 3;
			LeftMouseButtonClicked = 0;
			bool IsOkay = false;
			bool IsEnterPressed = false;
			bool fileExist = true;

			FilePath.push_back(keyWord(0, StartPointX, 1, 0, "", StartPointX));

			while (IsOkay == false) {

				KeyPressed_CHAR = cv::waitKey(1);
				KeyPressed_INT = KeyPressed_CHAR;
				cv::setMouseCallback(windowName, onMouse);
				LeftMouseButtonClicked = leftMouseKeyPressed();

				window.drawFillRect(windowSizeW / 2 - 300, windowSizeH / 2 - 100, 600, 170, 77, 77, 79, windowName, canvas);
				window.drawStrokeRect(windowSizeW / 2 - 300, windowSizeH / 2 - 100, 600, 170, 0, 0, 0, windowName, canvas);
				window.drawFillRect(windowSizeW / 2 - 250, windowSizeH / 2 - 20, 460, 33, 127, 125, 127, windowName, canvas);
				window.drawText(windowSizeW / 2 - 248, windowSizeH / 2 - 35, "File path", 255, 255, 255, 0.8, windowName, canvas);

				window.drawImage("Assets/Icons/hix.jpg", windowSizeW / 2 + 250, windowSizeH / 2 - 90, 32, 32, 77, 77, 79, COLOR_SCALE::RGB, true, windowName, canvas);
				window.drawFillRect(windowSizeW / 2 - 250 + 470, windowSizeH / 2 - 20, 75, 34, 100, 100, 100, windowName, canvas);
				window.drawText(windowSizeW / 2 + 233, windowSizeH / 2 + 3, "Open", 255, 255, 255, 0.6, windowName, canvas);

				window.drawFillRect(FilePath.at(FilePath.size() - 1).x + FilePath.at(FilePath.size() - 1).width, StartPointY - 15, 1, 20, 255, 255, 255, windowName, canvas);

				for (short i = 0; i < FilePath.size(); i++) {
					putText(canvas, FilePath.at(i).value, cv::Point(FilePath.at(i).x, StartPointY), 0, 0.6, cvScalar(255, 255, 255), 0, CV_AA);
				}

				if (MouseMovementCoords.x >= windowSizeW / 2 + 250 && MouseMovementCoords.x < windowSizeW / 2 + 250 + 32 && MouseMovementCoords.y >= windowSizeH / 2 - 90 && MouseMovementCoords.y < windowSizeH / 2 - 90 + 32 && LeftMouseButtonClicked == true) {
					IsOkay = true;
					StartPointX = 590;
					StartPointY = 150;
					window.drawFillRect(windowSizeW / 2 - 300, windowSizeH / 2 - 100, 600, 170, 30, 30, 30, windowName, canvas);
				}

				if (MouseMovementCoords.x >= windowSizeW / 2 - 250 + 470 && MouseMovementCoords.x < windowSizeW / 2 - 250 + 470 + 75 && MouseMovementCoords.y >= windowSizeH / 2 - 20 && MouseMovementCoords.y < windowSizeH / 2 - 20 + 34 && LeftMouseButtonClicked == true || IsEnterPressed == true) {


					std::string FileFullPath = keyWordVectorToString(FilePath);
					std::fstream file(FileFullPath);

					if (file.fail()) {
						fileExist = false;
					}
					while (file.good()) {
						StartPointX = 590;
						CurrentLine = 0;
						NumberLines = 0;
						Keys.clear();
						Keys.push_back(std::vector<keyWord>{keyWord(0, StartPointX, CurrentLine, 0, "\n", StartPointX)});
						std::string line;

						while (std::getline(file, line)) {
							ElementIDOnThatLine = 0;
							for (int i = 0; i < line.size(); i++) {
								KeyPressed_CHAR == line.at(i);
								KeyPressed_INT = (int)KeyPressed_CHAR;
								KeyPressed_STRING = KeyPressed_CHAR;

								if (KeyPressed_INT == 13) {
									Keys.at(CurrentLine).push_back(keyWord(0, 590, CurrentLine, 0, "\n"));
								}
								else {
									if (line.at(i) == 'm' || line.at(i) == '^' || line.at(i) == 'W' || line.at(i) == '=') {
										Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 23, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 21));
									}
									else if (line.at(i) == 'r' || line.at(i) == 't' || line.at(i) == 'j' || line.at(i) == 'i' || line.at(i) == 'f' || line.at(i) == 'l' || line.at(i) == '!' || line.at(i) == ':' || line.at(i) == '.') {
										Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 11, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 9));
									}
									else if (line.at(i) == 'y') {
										Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 12, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 10));
									}
									else if (line.at(i) == 'w' || line.at(i) == 'M') {
										Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 15, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 13));
									}
									else if (line.at(i) == '@' || line.at(i) == '%' || line.at(i) == '&' || line.at(i) == '+' || line.at(i) == '<' || line.at(i) == '>') {
										Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 19, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 17));
									}
									else {
										Keys.at(CurrentLine).push_back(keyWord(Keys.at(CurrentLine).size(), Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth, CurrentLine, 14, KeyPressed_STRING, Keys[CurrentLine][Keys.at(CurrentLine).size() - 1].allWidth + 15));
									}
								}
								ElementIDOnThatLine++;
							}
							CurrentLine++;
						}
					}



					IsEnterPressed = false;
				}
				if (fileExist == true) {
					window.drawFillRect(windowSizeW / 2 - 250, windowSizeH / 2 + 14, 300, 30, 77, 77, 79, windowName, canvas);
					window.drawText(windowSizeW / 2 - 250, windowSizeH / 2 + 34, "File is not existing", 0, 0, 255, 0.6, windowName, canvas);
				}

				if (KeyPressed_INT == -1) {}
				else if (KeyPressed_INT == 13) {
					IsEnterPressed = true;
				}
				else if (KeyPressed_INT == 8) {
					if (FilePath.size() - 1 != 0) {
						if (FilePath.at(FilePath.size() - 1).value == "") {
							FilePath.erase(FilePath.end() - 1);
						}
						else {
							FilePath.erase(FilePath.end() - 1);
						}
					}
				}
				else {
					window.drawFillRect(FilePath.at(FilePath.size() - 1).x + FilePath.at(FilePath.size() - 1).width, StartPointY - 20, 1, 20, 128, 128, 127, windowName, canvas);
					KeyPressed_STRING = KeyPressed_CHAR;
					if (KeyPressed_CHAR == 'm' || KeyPressed_CHAR == '^' || KeyPressed_CHAR == 'W' || KeyPressed_CHAR == '=') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 18, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 15));
					}
					else if (KeyPressed_CHAR == 'r' || KeyPressed_CHAR == 't' || KeyPressed_CHAR == 'j') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 8, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 5));
					}
					else if (KeyPressed_CHAR == 'i' || KeyPressed_CHAR == 'f' || KeyPressed_CHAR == 'l' || KeyPressed_CHAR == '!' || KeyPressed_CHAR == ':' || KeyPressed_CHAR == '.') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 6, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 6));
					}
					else if (KeyPressed_CHAR == 'y') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 10, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 7));
					}
					else if (KeyPressed_CHAR == 'w' || KeyPressed_CHAR == 'M') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth - 1, 1, 13, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 10));
					}
					else if (KeyPressed_CHAR == '@' || KeyPressed_CHAR == '%' || KeyPressed_CHAR == '&' || KeyPressed_CHAR == '+' || KeyPressed_CHAR == '<' || KeyPressed_CHAR == '>') {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 17, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 14));
					}
					else {
						FilePath.push_back(keyWord(FilePath.size(), FilePath.at(FilePath.size() - 1).allWidth, 1, 12, KeyPressed_STRING, FilePath.at(FilePath.size() - 1).allWidth + 12));
					}
				}

				cv::imshow(windowName, canvas);
			}
		}
		if (MouseMovementCoords.x >= windowSizeW - 43 && MouseMovementCoords.x < windowSizeW && MouseMovementCoords.y < 25 && LeftMouseButtonClicked == true) {
			return 0;
		}

		cv::imshow(windowName, canvas);
	}

	system("pause");
	cv::waitKey();
	return 0;
}