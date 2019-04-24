#include <iostream>
#include <iomanip>
#include "Map.h"
#include "Map.cpp"
using namespace std;


int main() {
	Map<int, int> map; 
	char menu = '0';
	int key, value;
	while (menu!='6')
	{
		cout << "\n1. Insert\n2. Remove\n3. List of keys\n4. List of values\n5. Clear\n6. Exit\n";
		cin >> menu;
		switch (menu)
		{
		case '1': cout << "Key and value: "; cin >> key >> value; map.insert(key, value); system("cls"); break;
		case '2': cout << "Key: "; cin >> key; map.remove(key); system("cls"); break;
		case '3': map.get_keys()->print_to_console(); break;
		//case '4': map.print_value_list(); break;
		case '5': map.~Map(); system("cls"); break;
		}
	}
	system("pause");
	return 0;
}