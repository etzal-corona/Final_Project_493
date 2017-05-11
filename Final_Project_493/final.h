#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <assert.h>


#define xbounds 100
#define ybounds 100
#define gamma .9
#define alpha .1
#define greedy .1


using namespace std;


class Agent {
public:
	void setinitilization();
	Agent(vector<double>rewardV);
	void move(int whatmove);
	int greedymover();
	int epsilonmover();
	int epsilonorgreedy();
	void TestA();
	void gridbumper();
	void updateqvalueandcheckforstoreandupdatemoney();
	double Qmaxfinder();
	void reset();
	double controller();
	//void goalchecker();
	//double getmoney();
private:
private:
	static double Qlist[100][100];
	static bool storelist[100][100];
	static double money[100][100];
	double Qvalue[100][100];
	double reward[100][100];
	double moneytotal;
	static int xbound;
	static int ybound;
	static int xstart;
	static int ystart;
	int xlocation;
	int ylocation;
	static int xgoal;
	static int ygoal;
	static int initilization;
	int counter;
};
double Agent::Qlist[100][100] = { 0 };
bool Agent::storelist[100][100] = { 0 };
double Agent::money[100][100] = { 0 };
int Agent::initilization = 0;
int Agent::xbound = 0;
int Agent::ybound = 0;
int Agent::xstart = 0;
int Agent::ystart = 0;
int Agent::xgoal = 0;
int Agent::ygoal = 0;
void Agent::setinitilization() {
	xbound = xbounds;
	ybound = ybounds;
	int Xarray[25];
	int randx, randy;
	for (int j = 0; j<100; j++) {
		for (int i = 0; i<100; i++)
		{
			storelist[i][j] = 0;//initilizing all indecies to 0
			money[i][j] = 0;//initilizing all indicies to 0
			double f = (double)rand() / RAND_MAX;//random double
			Qlist[i][j] = f;//setting q to a random double
		}
	}
	for (int i = 0; i<25; i++) {
		randx = rand() % 100;//random x values from 0 to 99
		Xarray[i] = randx;//storeing randx values in my store array
	}
	for (int i = 0; i<25;) {//setting 25 indicies of storelist to 1 and 25 indicies of money to 1000
		randy = rand() % 100;
		if (!(storelist[i][randy] == 1)) {//makes sure storelist has already been set to 1 at the random indicy
			storelist[Xarray[i]][randy] = 1;
			money[Xarray[i]][randy] = 1000;
			++i;
		}
	}
	cout << "What is the starting x location: ";
	cin >> xstart;
	cout << "What is the starting y location: ";
	cin >> ystart;
	cout << "What is the goal x location: ";
	cin >> xgoal;
	cout << "What is the goal y location: ";
	cin >> ygoal;
	for (int j = 0; j<100; j++) {
		for (int i = 0; i<100; i++) {
			//cout<<Qvalue[i][j];
			if (storelist[i][j] == 1) {
				//cout<<i<<','<<j<<endl;
			}
		}
	}
}
Agent::Agent(vector<double>rewardV) {
	for (int j = 0; j<100; j++) {
		for (int i = 0; i<100; i++) {
			Qvalue[i][j] = Qlist[i][j];
		}
	}
	xlocation = xstart;
	ylocation = ystart;
	counter = 0;
	moneytotal = 0;
	int index = 0;
	if (initilization == 0) {
		setinitilization();
	}
	++initilization;
	for (int j = 0; j<100; j++) {
		for (int i = 0; i<100; i++) {
			reward[i][j] = rewardV[index];
			++index;
		}
	}
}
void Agent::move(int whatmove) {
	if (whatmove == 1) {//moving north
		ylocation++;
		gridbumper();
	}
	if (whatmove == 2) {//moving south;
		ylocation--;
		gridbumper();
	}
	if (whatmove == 3) {//moving East
		xlocation--;
		gridbumper();
	}
	if (whatmove == 4) {//moving west
		xlocation++;
		gridbumper();
	}
}
int Agent::greedymover() {
	double north, south, east, west;
	if ((xlocation - 1)<0) {
		east = 0;
	}
	else {
		east = Qvalue[xlocation - 1][ylocation];
	}
	if ((xlocation + 1)>(xbounds - 1)) {
		west = 0;
	}
	else {
		west = Qvalue[xlocation + 1][ylocation];
	}
	if ((ylocation - 1)<0) {
		south = 0;
	}
	else {
		south = Qvalue[xlocation][ylocation - 1];
	}
	if ((ylocation + 1)>(ybounds - 1)) {
		north = 0;
	}
	else {
		north = Qvalue[xlocation - 1][ylocation];
	}
	if ((east>west) && (east >north) && (east>south)) {
		return 3;
	}
	if ((west>east) && (west>north) && (west>south)) {
		return 4;
	}
	if ((north>south) && (north>west) && (north>east)) {
		return 1;
	}
	if ((south>north) && (south>west) && (south>east))
	{
		return 2;
	}
}
int Agent::epsilonmover() {
	double north, south, east, west;
	if ((xlocation - 1)<0) {
		east = 0;
	}
	else {
		east = (double)rand() / RAND_MAX;
	}
	if ((xlocation + 1)>(xbounds - 1)) {
		west = 0;
	}
	else {
		west = (double)rand() / RAND_MAX;
	}
	if ((ylocation - 1)<0) {
		south = 0;
	}
	else {
		south = (double)rand() / RAND_MAX;
	}
	if ((ylocation + 1)>(ybounds - 1)) {
		north = 0;
	}
	else {
		north = (double)rand() / RAND_MAX;
	}
	if ((east>west) && (east >north) && (east>south)) {
		return 3;
	}
	if ((west>east) && (west>north) && (west>south)) {
		return 4;
	}
	if ((north>south) && (north>west) && (north>east)) {
		return 1;
	}
	if ((south>north) && (south>west) && (south>east))
	{
		return 2;
	}
}
int Agent::epsilonorgreedy() {
	int choice = rand() % 10;
	if (choice == 0) {
		return epsilonmover();
	}
	else {
		return greedymover();
	}
}

void Agent::TestA() {
	assert(xlocation >= 0);
	assert(xlocation <= xbound);
	assert(ylocation >= 0);
	assert(ylocation <= ybound);
}
void Agent::gridbumper() {
	int xboud = xbounds - 1;
	int yboun = ybounds - 1;
	if (xlocation>xbound) {
		xlocation = xbound;

	}
	if (xlocation<0) {
		xlocation = 0;

	}
	if (ylocation>ybound) {
		ylocation = ybound;

	}
	if (ylocation<0) {
		ylocation = 0;

	}
	TestA();
}
void Agent::updateqvalueandcheckforstoreandupdatemoney() {
	double Qmax = Qmaxfinder();
	Qvalue[xlocation][ylocation] = Qvalue[xlocation][ylocation] + alpha*(reward[xlocation][ylocation] + gamma*Qmax - Qvalue[xlocation][ylocation]);
	if (storelist[xlocation][ylocation] == 1) {
		moneytotal = 1000 + moneytotal;
		storelist[xlocation][ylocation] = 0;
	}
	moneytotal = moneytotal - 10;
}
double Agent::Qmaxfinder() {
	double north, south, east, west;
	if ((xlocation - 1)<0) {
		east = 0;
	}
	else {
		east = Qvalue[xlocation - 1][ylocation];
	}
	if ((xlocation + 1)>(xbounds - 1)) {
		west = 0;
	}
	else {
		west = Qvalue[xlocation + 1][ylocation];
	}
	if ((ylocation - 1)<0) {
		south = 0;
	}
	else {
		south = Qvalue[xlocation][ylocation - 1];
	}
	if ((ylocation + 1)>(ybounds - 1)) {
		north = 0;
	}
	else {
		north = Qvalue[xlocation - 1][ylocation];
	}
	if ((east>west) && (east >north) && (east>south)) {
		return Qvalue[xlocation - 1][ylocation];
	}
	if ((west>east) && (west>north) && (west>south)) {
		return Qvalue[xlocation + 1][ylocation];
	}
	if ((north>south) && (north>west) && (north>east)) {
		return Qvalue[xlocation][ylocation - 1];
	}
	if ((south>north) && (south>west) && (south>east))
	{
		return Qvalue[xlocation][ylocation + 1];
	}
}
void Agent::reset() {
	counter = 0;
	xlocation = xstart;
	ylocation = ystart;
	moneytotal = 0;
}
double Agent::controller() {
	int othercounter = 0;
	double moneyVal;
	for (int i = 0; i<100; i++) {
		do {
			move(epsilonorgreedy());
			updateqvalueandcheckforstoreandupdatemoney();
			counter++;
			othercounter++;
		} while (!(xlocation == xgoal) && !(ylocation == ygoal));
		//cout<<counter<<endl;
		moneyVal = moneytotal;
		reset();
	}
	//cout<<"wtf"<<endl;
	//cout<<othercounter<<','<<moneyVal<<endl;
	return moneyVal;
}