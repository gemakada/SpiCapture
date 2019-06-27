#include "SPIDevice.h"
#include"GPIO.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <future>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
using namespace exploringBB;
using namespace std::chrono;
void Start(int x) {
	SPIDevice *busDevice;
	ofstream outputFile;
	ifstream fs;
	std::string filename = "output.csv";
	fs.open(filename, std::ifstream::out | std::ifstream::trunc);
	int measures[288];
	union {
		unsigned short int in;
		unsigned char b[2];
	} meta;
	unsigned char* st;
	string file;

	GPIO* gpio_cnv = new GPIO(29);


	gpio_cnv->setDirection(OUTPUT);
	gpio_cnv->setValue(HIGH);

	gpio_cnv->setValue(LOW);
	int i = 1;


	busDevice = new SPIDevice(2, 0);

	st = busDevice->readDevice();
	meta.b[0] = st[1];
	meta.b[1] = st[0];
	//fs << x << "," << meta.in  << std::endl;
	file = busDevice->getFile();
	printf("Value  %d\n", meta.in);
	printf("Freq %d\n", busDevice->getSpeed());

	//}
	busDevice->close();
	fs.close();
	//cout << "End of SPI Test" << file << endl;


	//}
}


int main() {
	GPIO* voltage_shifters = new GPIO(56);
	voltage_shifters->setDirection(OUTPUT); 
	voltage_shifters->setValue(HIGH);
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 190;

	struct timespec hama, hama2;
	hama.tv_sec = 0;
	hama.tv_nsec = 1000;

	struct timespec tim6, tim7;
	tim6.tv_sec = 0;
	tim6.tv_nsec = 6;
	int wr;
	GPIO *open = new GPIO(29);
	open->setDirection(OUTPUT);
	open->setValue(LOW);
	unsigned char x;
	int values[288];
	SPIDevice *busDevice;
	ofstream outputFile;
	ofstream fs;
	std::string filename = "output.csv";
	fs.open(filename, std::ofstream::out | std::ofstream::trunc);
	int measures[288];

	nanosleep(&tim6, &tim7);
	busDevice = new SPIDevice(2, 0);


	busDevice->setMode(SPIDevice::MODE0);

	union {
		unsigned short int in;
		unsigned char b[2];
	} meta;
	unsigned char* st;
	string file;
	printf("%d\n", busDevice->getSpeed());



	int result;
	int delay = 1;
	GPIO* gpio_clk = new GPIO(80);
	GPIO* gpio_st = new GPIO(81);
	GPIO* gpio_eos = new GPIO(8);
	GPIO* gpio_cnv = new GPIO(29);
	GPIO* trg = new GPIO(9);
	gpio_eos->setDirection(INPUT);
	gpio_clk->setDirection(OUTPUT);
	gpio_st->setDirection(OUTPUT);
	trg->setDirection(INPUT);


	gpio_clk->setValue(LOW);
	nanosleep(&hama, &hama2);
	gpio_clk->setValue(HIGH);
	nanosleep(&hama, &hama2);

	gpio_clk->setValue(LOW);
	if (trg->getValue() == 1) {
		printf("TRG, CLK in Phase\n");
		//exit(0);
	}
	gpio_st->setValue(HIGH);
	nanosleep(&hama, &hama2);

	for (int i = 0; i < 12; i++) {

		gpio_clk->setValue(HIGH);
		nanosleep(&hama, &hama2);
		gpio_clk->setValue(LOW);
		nanosleep(&hama, &hama2);
	}

	gpio_st->setValue(LOW);
	nanosleep(&hama, &hama2);
	for (int i = 0; i < 86; i++) {

		gpio_clk->setValue(HIGH);
		nanosleep(&hama, &hama2);
		gpio_clk->setValue(LOW);
		nanosleep(&hama, &hama2);
	}

	gpio_clk->setValue(HIGH);
	nanosleep(&hama, &hama2);
	gpio_clk->setValue(LOW);
	nanosleep(&hama, &hama2);
	//gpio_cnv->setValue(HIGH);
	//std::future<void> fut = std::async(Start);
	for (int i = 0; i < 288; i++) {

		gpio_cnv->setDirection(OUTPUT);

		gpio_cnv->setValue(HIGH);
		nanosleep(&tim, &tim2);
		gpio_cnv->setValue(LOW);




		busDevice = new SPIDevice(2, 0);

		st = busDevice->readDevice();


		meta.b[0] = st[1];
		meta.b[1] = st[0];
		values[i] = meta.in;

		gpio_clk->setValue(HIGH);
		nanosleep(&hama, &hama2);
		gpio_clk->setValue(LOW);
		nanosleep(&hama, &hama2);


	}



	gpio_st->setValue(HIGH);
	result = gpio_eos->getValue();

	while (result == 0) {
		nanosleep(&hama, &hama2);
		gpio_clk->setValue(HIGH);

		result = gpio_eos->getValue();
		printf("%d\n", result);
		nanosleep(&hama, &hama2);
		gpio_clk->setValue(LOW);

	}

	gpio_clk->setValue(HIGH); 
	nanosleep(&hama, &hama2);


	gpio_clk->setValue(LOW);
	gpio_st->setValue(LOW);
	nanosleep(&hama, &hama2);

	for (int i = 0; i < 288; i++) {
		fs << i << ";" << values[i] << std::endl;
		printf("%d, %d\n", i, values[i]);
	}


	fs.close();
}
