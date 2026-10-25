#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;

    cout << "Enter number of computers: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of computers!" << endl;
        return 0;
    }

    vector<vector<int>> adj(n + 1);

    cout << "Enter number of cable connections: ";
    cin >> m;

    if (m < 0) {
        cout << "Invalid number of connections!" << endl;
        return 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cout << "Enter connected computers: ";
        cin >> u >> v;

        if (u < 1 || u > n || v < 1 || v > n) {
            cout << "Invalid computer number!" << endl;
            return 0;
        }

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int choice;
    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Display Computer Network" << endl;
        cout << "2. Check Direct Connection" << endl;
        cout << "3. Add New Computer and Connections (Mod A)" << endl;
        cout << "4. Remove Failed Cable (Mod B)" << endl;
        cout << "5. Count Direct Connections (Mod C)" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nComputer Network:\n";
                for (int i = 1; i <= n; i++) {
                    cout << "Computer " << i << " -> ";
                    for (int v : adj[i]) {
                        cout << v << " ";
                    }
                    cout << endl;
                }
                break;

            case 2: {
                int a, b;
                cout << "\nEnter two computers to check: ";
                cin >> a >> b;

                if (a < 1 || a > n || b < 1 || b > n) {
                    cout << "Invalid computer number!" << endl;
                    break;
                }

                bool connected = false;
                for (int v : adj[a]) {
                    if (v == b) {
                        connected = true;
                        break;
                    }
                }

                if (connected) cout << "Direct connection exists.\n";
                else cout << "No direct connection exists.\n";
                break;
            }

            case 3: {
                n++;
                adj.push_back(vector<int>());
                cout << "Added Computer " << n << "." << endl;

                int num_conns;
                cout << "Enter number of connections: ";
                cin >> num_conns;

                for (int i = 0; i < num_conns; i++) {
                    int target;
                    cout << "Connect Computer " << n << " to: ";
                    cin >> target;
                    if (target >= 1 && target < n) {
                        adj[n].push_back(target);
                        adj[target].push_back(n);
                    } else {
                        cout << "Invalid computer number!" << endl;
                        i--;
                    }
                }
                break;
            }

            case 4: {
                int u, v;
                cout << "Enter computers with failed cable: ";
                cin >> u >> v;

                if (u >= 1 && u <= n && v >= 1 && v <= n) {
                    auto it1 = find(adj[u].begin(), adj[u].end(), v);
                    auto it2 = find(adj[v].begin(), adj[v].end(), u);

                    if (it1 != adj[u].end() && it2 != adj[v].end()) {
                        adj[u].erase(it1);
                        adj[v].erase(it2);
                        cout << "Successfully removed failed cable.\n";
                    } else {
                        cout << "No cable connection exists.\n";
                    }
                } else {
                    cout << "Invalid computer numbers!" << endl;
                }
                break;
            }

            case 5:
                cout << "\n--- Direct Connections Count ---" << endl;
                for (int i = 1; i <= n; i++) {
                    cout << "Computer " << i << " has " 
                         << adj[i].size() << " connection(s)." << endl;
                }
                break;

            case 6:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}
