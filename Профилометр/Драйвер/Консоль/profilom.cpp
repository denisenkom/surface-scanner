// profilom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "driver.h"

char * error_str = "ERROR: ";

typedef void (*t_command)();

struct menuitem {
	char* name;
	t_command fn;
	menuitem() {}
	menuitem(char *name, t_command fn)
		: name(name), fn(fn)
	{
	}
};

driver driver;

void fsetup()
{
	std::cout << "Current settings:\n\tport=" << driver.port.c_str() << "\n\tmode=\"" << driver.mode.c_str() << "\"\n";
	std::cout << "Do you want to change this?(Y/N)>";
	char ans;
	std::cin >> ans;
	if (ans == 'n' || ans == 'N') return;
	std::cout << "Enter port name: ";
	char buf[256];
	std::cin >> buf;
	driver.port = buf;
	std::cout << "Enter port mode: ";
	std::cin >> buf;
	std::cin.getline(buf + strlen(buf), 256 - strlen(buf));
	driver.mode = buf;
	try
	{
		driver.close_port();
		driver.open_port();
	}
	catch (std::runtime_error &err)
	{
		std::cout << error_str << err.what() << std::endl;
	}
}

void ftest()
{
	try
	{
		std::cout << "Testing...";
		if (driver.test())
			std::cout << " ok.\n";
		else
			std::cout << " not ok\n";
	}
	catch (std::runtime_error &err)
	{
		std::cout << error_str << err.what() << std::endl;
	}
}

void fstep()
{
	std::cout << "Enter ammount of steps (>0-right, <0-left):";
	int num;
	std::cin >> num;
	try
	{
		std::cout << "Making steps...";
		driver.steps(num);
		/*while (num != 0)
		{
			if (num > 0)
			{
				driver.right_step();
				num--;
			}
			else
			{
				driver.left_step();
				num++;
			}

		}*/
		std::cout << "ok\n";
	}
	catch (std::runtime_error &err)
	{
		std::cout << error_str << err.what() << std::endl;
	}
}

void facp()
{
	std::cout << "Enter ammount of ADC scans 0..255: ";
	unsigned num;
	std::cin >> num;
	short* data = new short[num];
	try
	{
		std::cout << "Reading acp...";
		driver.request_acp(num, data);
		std::cout << "ok\n";
		for (unsigned char i = 0; i < num; i++)
		{
			if (i % 5 == 0) std::cout << std::endl;
			std::cout << '\t' << data[i];
		}
	}
	catch (std::runtime_error &err)
	{
		std::cout << error_str << err.what() << std::endl;
	}
	delete data;
}

void fdisplay()
{
	unsigned char dig[6];
	try
	{
		std::cout << "Queryng display...";
		driver.get_digital(dig);
		std::cout << "ok\n";
		for (int i = 0; i < 6; i++)
			std::cout << unsigned(dig[i]) << ' ';
		std::cout << std::endl;
	}
	catch (std::runtime_error &err)
	{
		std::cout << error_str << err.what() << std::endl;
	}
}

void fkeys()
{
	std::cout << "Enter number representing key 0..31: ";
	int key;
	do
	{
		std::cin >> key;
		if (key < 0 && key > 31)
			std::cout << "Invalid number, must be in range 0..31: ";
	}
	while (key < 0 && key > 31);
	try
	{
		std::cout << "Setting key...";
		driver.set_digital(key);
		std::cout << "ok\n";
	}
	catch (std::runtime_error &err)
	{
		std::cout << error_str << err.what() << std::endl;
	}
}

void run_menu(std::map<int, menuitem> &menu)
{
	using std::cout;
	using std::cin;
	using std::map;
	using std::endl;
	while (1)
	{
		for (map<int, menuitem>::const_iterator i = menu.begin(); i != menu.end(); i++)
			cout << '\t' << i->first << '-' << i->second.name << endl;
		cout << "\tq-quit\n";
		cout << ">";
		char q;
		cin	>> q;
		if (q == 'q')
			return;
		menu[q-'0'].fn();
	}
}

int main()
{
	using std::cout;
	using std::cin;
	using std::map;
	using std::pair;
	using std::endl;

	typedef pair<int, menuitem> mpair;
	map<int, menuitem> mainmenu;
	mainmenu.insert(mpair(1, menuitem("Setup", &fsetup)));
	mainmenu.insert(mpair(2, menuitem("Test", &ftest)));
	mainmenu.insert(mpair(3, menuitem("ADC", &facp)));
	mainmenu.insert(mpair(4, menuitem("Step driver", &fstep)));
	mainmenu.insert(mpair(5, menuitem("Digital display", &fdisplay)));
	mainmenu.insert(mpair(6, menuitem("Keys control", &fkeys)));

	cout << "Testing program for profilometer.\n";
	cout << "Main menu\n";
	run_menu(mainmenu);
	return 0;
}
