/*
10:52 PM - millinon: map every key to capslock
10:52 PM - millinon: ultimate cool lock
*/

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

class Key{
public:
	Key(short _keyIn, short _keyOut);
	void HandleEvents();
private:
	bool keyDown;
	short keyIn;
	short keyOut;
};

Key::Key(short _keyIn, short _keyOut)
{
	keyIn = _keyIn;
	keyOut = _keyOut;
	keyDown = false;
}

void Key::HandleEvents()
{
	if (GetAsyncKeyState(keyIn) && !keyDown)
	{
		keybd_event((unsigned char)keyOut, 0, 0, 0);
		keyDown = true;
	}
	if (!GetAsyncKeyState(keyIn) && keyDown)
	{
		keybd_event((unsigned char)keyOut, 0, KEYEVENTF_KEYUP, 0);
		keyDown = false;
	}
}

int main()
{
	string keyChars = "abcdefghijklmnopqrstuvwxyz";
	vector<char> KeyCharVec;
	std::vector<short> KeyVec;
	std::vector<Key> Keys;

	//Turn the string into a vector of characters.
	for (int i = 0; i < keyChars.length(); i++)
	{
		KeyCharVec.push_back(keyChars.substr(i, 1).c_str()[0]);
	}

	//VkKeyScan through all those chars for their corresponding shorts
	for (int i = 0; i < KeyCharVec.size(); i++)
	{
		KeyVec.push_back(VkKeyScan(KeyCharVec[i]));
	}

	//Create a new key class for all those.
	for (int i = 0; i < KeyVec.size(); i++)
	{
		Keys.push_back(Key(KeyVec[i], VK_CAPITAL));
	}
	
	while (1)
	{
		for (int i = 0; i < Keys.size(); i++)
		{
			Keys[i].HandleEvents();
		}
	}
	
	return 0;
}
