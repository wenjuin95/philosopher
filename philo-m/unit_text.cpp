#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

#define MAX_PHILO 200

int main()
{
	int eating_count[MAX_PHILO] = {0}; // Array to store eating counts, initialized to 0
	int total_eat = 0;
	std::string line;
	int time;
	int philosopher_id;

	std::ifstream file("philo.txt");
	if (!file.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return 1;
	}


	while (std::getline(file, line))
	{
		if (line.find("is eating") != std::string::npos)
		{
			std::istringstream iss(line); // Use istringstream to parse the line
			iss >> time >> philosopher_id; // Extract timestamp and philosopher ID
			if (philosopher_id > 0 && philosopher_id < MAX_PHILO)
			{
				eating_count[philosopher_id]++; // Increment the count for this philosopher
			}
			total_eat++;
		}
	}

	// Print the eating count for each philosopher
	for (int i = 1; i < MAX_PHILO; ++i)
	{
		if (eating_count[i] > 0)
		{
			std::cout << "Philosopher " << i << " eat " << eating_count[i] << " time" << std::endl;
		}
	}
	std::cout << "Total eat: " << total_eat << std::endl;

	file.close();
	return 0;
}
