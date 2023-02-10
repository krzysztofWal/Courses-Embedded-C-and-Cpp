// Section 19
// Challenge 1
// Formatting output
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
//#include <typeinfo>

struct City {
    std::string name;
    long population;
    double cost;
};

// Assume each country has at least 1 city
struct Country {
    std::string name;
    std::vector<City> cities;
};

struct Tours {
    std::string title;
    std::vector<Country> countries;
};

int middleStartPosition(int fieldLength, std::string stringName) {
	return (fieldLength - stringName.length())/2;
}


int main()
{
    Tours tours
        { "Tour Ticket Prices from Miami",
            {
                {
                    "Colombia", { 
                        { "Bogota", 8778000, 400.98 },
                        { "Cali", 2401000, 424.12 },
                        { "Medellin", 2464000, 350.98 },
                        { "Cartagena", 972000, 345.34 } 
                    },
                },
                {
                    "Brazil", { 
                        { "Rio De Janiero", 13500000, 567.45 },
                        { "Sao Paulo", 11310000, 975.45 },
                        { "Salvador", 18234000, 855.99 }
                    },
                },
                {
                    "Chile", { 
                        { "Valdivia", 260000, 569.12 }, 
                        { "Santiago", 7040000, 520.00 }
                },
            },
                { "Argentina", { 
                    { "Buenos Aires", 3010000, 723.77 } 
                } 
            },
        }
    };
	
	int fieldOneLength {20};
	int fieldTwoLength {30};
	int fieldThreeLength {20};
	int fieldFourLength {20};
	int wholeField {fieldOneLength + fieldTwoLength + fieldThreeLength + fieldFourLength};

    // Unformatted display so you can see how to access the vector elements

//	std::cout << middleStartPosition(wholeField,tours.title);
    std::cout << std::setw(middleStartPosition(wholeField,tours.title)) << "" << tours.title << std::endl <<std::endl;
	std::cout << std::setw(middleStartPosition(fieldOneLength, "Country")) << "" << "Country" << std::setw(middleStartPosition(fieldOneLength, "Country")) << "" 
			<< std::setw(middleStartPosition(fieldTwoLength, "City")) << "" << "City" << std::setw(middleStartPosition(fieldTwoLength, "City")) << ""
			<< std::setw(middleStartPosition(fieldThreeLength, "Population")) << "" << "Population" << std::setw(middleStartPosition(fieldThreeLength, "Population")) << "" 
			<< std::setw(middleStartPosition(fieldFourLength, "Price")) << "" << "Price" << std::endl;
	
	std::cout << std::setw(wholeField) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
 
	std::cout << std::setprecision(2) << std::fixed;
 
 
    for(auto country : tours.countries) {
		for(size_t i {0}; i < country.cities.size(); i++) {
				std::cout << std::setw(fieldOneLength) << ((i == 0) ? country.name : " ")  << std::setw(fieldTwoLength) << country.cities.at(i).name <<
						std::setw(fieldThreeLength) << country.cities.at(i).population <<
						std::setw(fieldFourLength) << country.cities.at(i).cost << std::endl;
		}
    }
	
	
	//sstd::cout << typeid(Tours).name() << std::endl;
    std::cout << std::endl << std::endl;
    return 0;
}