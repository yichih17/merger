#include<iostream>
#include<fstream>
#include<string>
#define algorithm_number 17
#define UE_level 12
#define parameter_number 28
#define UE_mode_number 2

using namespace std;

int main()
{
	int mode = 0;
	cout << "Input mode number (uniform = 0, hotspot = 1):";
	cin >> mode;
	
	char *mode_name;
	if (mode == 0)
	{
		mode_name = new char[1];
		mode_name = "";
	}
	else
	{
		mode_name = new char[3];
		mode_name = "hs_";
	}

	double result[algorithm_number][UE_level][parameter_number] = { 0 };
	char algorithm[][10] = { "DSO_0_0", "DSO_0_25", "DSO_0_50", "DSO_0_75", "DSO_0_100", "DSO_1_0", "DSO_1_25", "DSO_1_50", "DSO_1_75", "DSO_1_100", "DSO_2_0", "DSO_2_25", "DSO_2_50", "DSO_2_75", "DSO_2_100", "Capa", "SINR" };
	char parameter[][25] = { "Outage_UE", "Avg_T", "T_SD", "Avg_UE_number", "UE_number_SD", "Avg_Capacity_UE", "Capacity_SD_UE", "Avg_T_UE", "T_SD_UE",
							  "Avg_T_LTE", "Avg_T_WiFi", "T_SD_WiFi", "Avg_UE_number_LTE", "Avg_UE_number_WiFi", "UE_number_SD_WiFi",
							  "Avg_Capacity_UE_LTE", "Capacity_SD_UE_LTE", "Avg_Capacity_UE_WiFi", "Capacity_SD_UE_WiFi", "Avg_T_UE_LTE", "Avg_T_UE_WiFi", "T_SD_UE_WiFi",
							  "Satisfied_UE_number", "Throughput", "Satisfaction", "DB50_Satisfied%", "DB100_Satisfied%", "DB300_Satisfied%" };

	for (int i = 0; i < algorithm_number; i++)
	{
		for (int j = 0; j < UE_level; j++)
		{
			char filename[100];
			sprintf_s(filename, "%sUE%d_%s_result.csv", mode_name, (j + 1) * 1000, algorithm[i]);
			//cout << filename << endl;
			ifstream ReadResult;
			ReadResult.open(filename, ios::in);
			if (ReadResult.fail())
				cout << filename << " 開啟失敗." << endl;
			else
			{
				string in;
				int n = 0;
				while (ReadResult >> in)
				{
					n++;
					int size = in.size();
					int begin = 0;
					for (int k = 0; k < parameter_number; k++)
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
				for (int k = 0; k < parameter_number; k++)
					result[i][j][k] /= n;

			}
			ReadResult.close();
		}
	}

	fstream WriteResult;
	char ResultName[] = "simulation_result.csv";
	WriteResult.open(ResultName, ios::out | ios::trunc);
	if (WriteResult.fail())
		cout << ResultName << " 開啟失敗." << endl;
	else
	{
		for (int k = 0; k < parameter_number; k++)
		{
			WriteResult << parameter[k] << ",";
			for (int n = 0; n < UE_level; n++)
				WriteResult << (n + 1) * 1000 << ",";
			WriteResult << endl;
			for (int i = 0; i < algorithm_number; i++)
			{
				WriteResult << algorithm[i] << ",";
				for (int j = 0; j < UE_level; j++)
				{
					if (j != UE_level - 1)
						WriteResult << result[i][j][k] << ",";
					else
						WriteResult << result[i][j][k] << endl;
				}
			}
			WriteResult << endl;
		}
	}
	WriteResult.close();
	return 0;
}