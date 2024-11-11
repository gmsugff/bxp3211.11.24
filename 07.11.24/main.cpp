#include <iostream> 
#include <string>
#include <cpr/cpr.h>   
#include "nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;

class Exception
{
public:
    explicit Exception(const std::string& message) : message{ message } {}
    std::string getMessage() const { return message; }
private:
    std::string message;
};


json foo(const std::string& url) {
    cpr::Response r = cpr::Get(cpr::Url{ "https://www.dnd5eapi.co" + url });

    if (r.status_code == 200) {
        return json::parse(r.text);
    }
    else {
        cout << "Error: " << r.error.message << endl;
        throw Exception("Failed to fetch data from the URL.");
    }
}
void r(string htps) {
    cpr::Response r = cpr::Get(cpr::Url{ "https://www.dnd5eapi.co/api/"+htps });

    if (r.status_code == 200) {
        json json_response = json::parse(r.text);
        cout << "name: " << json_response["name"] << '\n';
        cout << "index: " << json_response["index"] << '\n';
        cout << "url: " << json_response["url"] << '\n';

        for (const auto& s : json_response["subsections"]) {
            cout << "\tSubsections name: " << s["name"] << '\n';
            cout << "\tSubsections index: " << s["index"] << '\n';
            cout << "\tSubsections url: " << s["url"] << '\n';

            cout << '\n' << '\n' << '\n' << '\n';
            try {
                auto r2 = foo(s["url"]);
                cout << "Subsection details:\n";
                cout << "\tName: " << r2["name"] << '\n';
                cout << "\tIndex: " << r2["index"] << '\n';
                if (r2.contains("desc")) {
                    cout << "\tDescription: " << r2["desc"] << '\n';
                }
                cout << '\n' << '\n' << '\n' << '\n';
            }
            catch (const Exception& e) {
                cout << e.getMessage() << '\n';
            }
        }
    }
    else {
        cout << "Error: " << r.error.message << endl;
    }

}
void ran() {
    int a;
    string https;
    while (true)
    {
    cin >> a;
    cout << "1-adventuring" << "2-appendix" << "3-combat"<<"4-equipment"<<"5-spellcasting"<<"6-using-ability-scores"<<endl;
        switch (a)
        {
        case 1:
             r("rules/adventuring");
             break;
        case 2:
            r("rules/appendix");
            break;
        case 3:
            r("rules/combat");
            break;
        case 4:
            r("rules/equipment");
            break;
        case 5:
            r("rules/spellcasting");
            break;
        case 6:
            r("rules/using-ability-scores");
            break;
        default:
            break;
        }
    }
    

}
int main() {
    ran();
}
