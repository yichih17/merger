#include<iostream>
#include<fstream>
#include<string>
#define algorithm_number 5
#define UE_level 15
#define parameter 23

using namespace std;

int main()
{
	//cout << "輸入檔案個數 : ";
	//cin >> file_num;

	double result[algorithm_number][UE_level][parameter] = { 0 };

	for (int i = 0; i < algorithm_number; i++)
	{
		char *algorihm_name;
		switch (i)
		{
		case 0:
			algorihm_name = new char[6];
			algorihm_name = "dso_0";
			break;
		case 1:
			algorihm_name = new char[6];
			algorihm_name = "dso_1";
			break;
		case 2:
			algorihm_name = new char[6];
			algorihm_name = "dso_2";
			break;
		case 3:
			algorihm_name = new char[5];
			algorihm_name = "minT";
			break;
		case 4:
			algorihm_name = new char[5];
			algorihm_name = "SINR";
			break;
		default:
			break;
		}

		for (int j = 0; j < UE_level; j++)
		{
			char filename[50];
			sprintf_s(filename, "hs_%s_UE%d_result.csv", algorihm_name, (j + 1) * 1000);
			ifstream file;
			file.open(filename, ios::in);
			if (file.fail())
				cout << filename << " 開啟失敗." << endl;
			else
			{
				string in;
				int n = 0;
				while (file >> in)
				{
					n++;
					int size = in.size();
					int begin = 0;
					for (int k = 0; k < parameter; k++)
					{
						int pos = in.find(",", begin);
						if (pos < size)
						{
							string s = in.substr(begin, pos - begin);
							result[i][j][k] += stod(s);
							begin = pos + 1;
						}
					}
				}
				for (int k = 0; k < parameter; k++)
					result[i][j][k] /= n;

			}
		}
	}

	fstream outcome;
	char outcome_name[] = "simulation_result.csv";
	outcome.open(outcome_name, ios::out | ios::trunc);
	if (outcome.fail())
		cout << outcome_name << " 開啟失敗." << endl;
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if(i==0)
				outcome << " ,outage_UE,avg_T,stdev_T,avg_UE_number,stdev_UE_number,avg_capacity_UE,stdev_capacity_UE,avg_T_UE,stdev_T_UE,avg_T_LTE,avg_T_WIFI,stdev_T_WIFI,"
				<< "avg_UE_number_LTE,avg_UE_number_WIFI,stdev_UE_number_WIFI,avg_capacity_LTEUE,stdev_capacity_UE_LTE,avg_capacity_WIFIUE,stdev_capacity_UE_WIFI,avg_T_UE_LTE,"
				<< "avg_T_UE_WIFI,stdev_T_UE_WIFI,DB_satisfied";
			else
				outcome << ", ,outage_UE,avg_T,stdev_T,avg_UE_number,stdev_UE_number,avg_capacity_UE,stdev_capacity_UE,avg_T_UE,stdev_T_UE,avg_T_LTE,avg_T_WIFI,stdev_T_WIFI,"
				<< "avg_UE_number_LTE,avg_UE_number_WIFI,stdev_UE_number_WIFI,avg_capacity_LTEUE,stdev_capacity_UE_LTE,avg_capacity_WIFIUE,stdev_capacity_UE_WIFI,avg_T_UE_LTE,"
				<< "avg_T_UE_WIFI,stdev_T_UE_WIFI,DB_satisfied";
		}
		outcome << endl;

		for (int j = 0; j < UE_level; j++)
		{
			outcome << (j + 1) * 1000 << ",";
			for (int i = 0; i < algorithm_number; i++)
			{
				for (int k = 0; k < parameter; k++)
				{
					if (k != parameter - 1)
						outcome << result[i][j][k] << ",";
					else
						outcome << result[i][j][k] << "," << ",";
				}
			}
			outcome << endl;
		}
	}
	
	return 0;
}