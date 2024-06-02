#include "../utils/andreinet.h"
using namespace std;

net n({2, 4, 1});

ofstream py("../python/data.txt");

void saveWeights()
{
    ofstream wo("save.txt");
    if (!wo.is_open()) {
        cout << "Error opening save file!" << endl;
        return;
    }

    for (int i = 0; i < n.layers.size(); i++)
    {
        for (int j = 0; j < n.layers[i].nodes.size(); j++)
        {
            for (int k = 0; k < n.layers[i].nodes[j].next.size(); k++)
            {
                wo << n.layers[i].nodes[j].next[k].weight << " ";
            }
            wo << "\n";
        }
    }
    if (wo.fail()) {
        cout << "Error writing to save file!" << endl;
    }
    wo.close();
    if (wo.fail()) {
        cout << "Error closing the save file!" << endl;
    }
}

void importWeights()
{
    ifstream wi("save.txt");
    if (!wi.is_open()) {
        cout << "Error opening save file!" << endl;
        return;
    }

    for (int i = 0; i < n.layers.size(); i++)
    {
        for (int j = 0; j < n.layers[i].nodes.size(); j++)
        {
            for (int k = 0; k < n.layers[i].nodes[j].next.size(); k++)
            {
                if (!(wi >> n.layers[i].nodes[j].next[k].weight)) {
                    cout << "Error reading weight for layer " << i << ", node " << j << ", weight " << k << endl;
                    wi.close();
                    return;
                }
            }
        }
    }
    if (wi.fail() && !wi.eof()) {
        cout << "Error reading from save file!" << endl;
    }
    wi.close();
    
    
}


void displayMenu()
{
    cout << BOLDBLUE << "[?] WAS MOCHTEN SIE TUN?\n"
        << YELLOW <<"    [1]Netz probieren"
        << RED << "(moglich untrainiert)"
        << YELLOW << "\n    [2]Netz trainieren"
        << "\n    [3]Gewichte speichern"
        << "\n    [4]Gewichte importieren"
        << "\n    [5]Netz selbst testen"
        << "\n    [6]Grafik erstellen"
        << "\n    [99]Beenden\n>>>"
        << RESET;
}

void runDemo2(string outputfile)
{
    cout << BOLDGREEN << "\n[+]INIT DEMO2" << RESET;
    
    /*
    Aktivierungsfunktionen:
    0 - ReLU
    1 - Sigmoid
    2 - Softmax
    */
    t.start(); // Timer starten

    // Aktivierungsfunktionen für die layeren festlegen
    n.noActivate(0);     // Eingangs-layer deaktivieren
    n.setActivate(1, 1); // ReLU-Aktivierung für die versteckte Layer festlegen
    n.setActivate(2, 1); // Sigmoid-Aktivierung für die Ausgangs-layer festlegen
    n.connectLayers();   // layers verbinden

    // Gewichte und Bias initialisieren
    n.setWeightAll(1); // Alle Gewichte auf 1 setzen (default))
    n.setBiasAll(0);   //  Bias auf 0 setzen (default)

    // Eingabemerkmale: [Studierte Stunden, Schlaf (Stunden)]
    vector<pair<double, double>> input = {
        // Durchfallwerte
        {2, 4},
        {3, 5},
        {1, 3},
        {4, 2},
        {2, 1},
        {3, 2},
        {1, 5},
        {4, 3},
        {2, 6},
        {3, 1},
        {2, 2},
        {1, 4},
        {4, 5},
        {3, 6},
        {1, 1},
        {4, 1},
        {2, 2},
        {3, 3},
        {1, 2},
        {4, 4},
        // Bestandene Werte
        {8, 10},
        {9, 11},
        {7, 9},
        {10, 8},
        {8, 7},
        {9, 8},
        {7, 11},
        {10, 9},
        {8, 12},
        {9, 7},
        {8, 13},
        {7, 10},
        {10, 11},
        {9, 12},
        {7, 7},
        {10, 7},
        {8, 8},
        {9, 9},
        {7, 8},
        {10, 10},
        {6, 6},
        {11, 11},
        {5, 5},
        {12, 12},
        {6, 5}};

    // Erwartete Ausgaben: 0 für Durchfall, 1 für Bestanden
    vector<double> expected = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1};

    pair<
        vector<
            pair<double, double>>,
        vector<double>>
        trainingData;
    trainingData.first = input;
    trainingData.second = expected;

    int epochs = 100000;
    double learningRate = 0.06;

    int choice;
    /*
    cout << YELLOW << "[?] WAS MÖCHTEN SIE TUN?\n    [1]Netz probieren"
    << RED << "(moglich untrainiert)"
    << YELLOW << "\n    [2]Netz trainieren"
    << "\n    [3]Gewichte speichern"
    << "\n    [4]Gewichte importieren"
    << "\n    [5]Netz selbst testen"
    << "\n    [6]Grafik erstellen"
    << "\n    [99]Beenden\n>>>";
    */
    while (true)
    {
        cls
        displayMenu();
        cin >> choice;
        if (choice == 99)
        {
            cls
            cout << BOLDRED << "\n[+]BEENDEN" << RESET;
            break;
        }
        else if (choice == 1)
        {
            cls
            cout << RED << "\n[-]MOGLICH UNTRAINIERTES NETZ" << RESET;
            n.testNet(trainingData, true);
            cout << YELLOW << "\n[ENTER]" << RESET << " um fortzufahren";
            cin.get();
            cin.get();
            cls
        }
        else if (choice == 2)
        {
            cls
            cout << BOLDCYAN << "\n[+]TRAINIERE NETZ(-1 EXIT)" << RESET << "\n";
            cout << YELLOW << "[?] WIE VIELE EPOCHS: ";
            cin >> epochs;
            if(epochs == -1)
                continue;
            cout << YELLOW << "[?] LERNRATE: ";
            cin >> learningRate;
            if(learningRate == -1)
                continue;
            cout << RESET;
            n.backPropagate(trainingData, epochs, learningRate);
            cout << BOLDCYAN << "\n[+]NACH DEM TRAINING";
            n.testNet(trainingData, true);
            n.printCosts();
            cout << YELLOW << "\n[ENTER]" << RESET << " um fortzufahren";
            cin.get();
            cin.get();
        }
        else if (choice == 3)
        {
            cls
            saveWeights();
            cout << BOLDCYAN << "\n[+]GEWICHTE GESPEICHERT" << RESET;
            cout << YELLOW << "\n[ENTER]" << RESET << " um fortzufahren";
            cin.get();
            cin.get();
        }         
        else if (choice == 4)
        {
            cls
            importWeights();
            cout << BOLDCYAN << "\n[+]GEWICHTE IMPORTIERT" << RESET;
            cout << YELLOW << "\n[ENTER]" << RESET << " um fortzufahren";
            cin.get();
            cin.get();
        }           
        else if (choice == 5)
        {
            cls
            double threshold = 0.708253;
            cout << BOLDCYAN << "\n[+]NETZ SELBST TESTEN(-1 fur rausgehen)" << RESET;
            cout << RED << "\n[!]MOGLICH UNTRAINIERTES NETZ" << RESET;
            cout << MAGENTA << "\n[*]THRESHOLD: " << threshold << "\n";
            n.clean();
            // nicht Escape drücken
            double testStudy;
            double testSleep;
            pair<double, double> testInput;
            while (true)
            {
                cout << BOLDBLUE << "\n[?]Stunden des Lernens und Schlafstunden eingeben: ";
                cin >> testStudy;
                if (testStudy == -1)
                    break;
                cin >> testSleep;
                if (testSleep == -1)
                    break;
                testInput = {testStudy, testSleep};
                n.clean();
                n.clearSSR();
                n.setInputFromVector(testInput);
                n.passValues();
                double value = n.layers.back().nodes.back().value;
                cout << "    [*]Testwert: " << value;
                if (value > threshold)
                {
                    cout << GREEN << "    \n[+]Bestanden\n";
                    py << testStudy << "," << testSleep << ",1";
                    py << ",black\n";
                }
                else
                {
                    cout << RED << "    \n[-]Durchgefallen\n";
                    py << testStudy << "," << testSleep << ",0";
                    py << ",black\n";
                }
            }
            cout << RESET;
        }
        else if (choice == 6)
        {
            cls
            cout << BOLDCYAN << "\n[+]GRAFIK ERSTELLEN" << RESET;
            for (int i = 0; i < input.size(); i++)
            {
                py << input[i].first << "," << input[i].second << "," << expected[i];
                if (expected[i] == 1)
                    py << ",green\n";
                else
                    py << ",red\n";
            }
            py.close();
            // saveWeights();
            system("python ../python/main.py");
            cout << RESET;
        }
    }

    
    
    cout << RESET;
    t.stop();
    u.logTime();
    l.flush();
}
