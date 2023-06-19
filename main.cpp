#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Function to remove the last octet from an IP address
string removeLastOctet(const string& ipAddress) {
    string result = "";
    size_t lastDotPos = ipAddress.find_last_of('.');
    if (lastDotPos != string::npos) {
        result = ipAddress.substr(0, lastDotPos);
    }
    return result;
}

// Function to display the subnetting table
void table(int numSubnets, const string& ipAddress, int maxHosts) {
    string modifiedIP = removeLastOctet(ipAddress);

    cout << "\nName\t\t" << "Network ID\t\t" << "Host Range\t\t" << "Broadcast\t\t";
    for (int u = 0; u <= numSubnets - 1; u++) {
        int hosts = maxHosts + 2;

        if (u != numSubnets) {
            cout << "\n" << u + 1 << ".Subnet\t";
        }
        else {
            cout << "\n" << ".Reserved Subnet\t";
        }

        cout << modifiedIP << "." << u * hosts << "\t";
        cout << modifiedIP << "." << u * hosts + 1 << "-";
        cout << modifiedIP << "." << u * hosts + hosts - 2 << "\t";
        cout << modifiedIP << "." << u * hosts + hosts - 1 << "\t";
    }
    cout << endl;
}

// Calculate new CIDR notation
void newCIDR(const string& ipAddress, int cidr, int numSubnets, int numDevices) {
    int subnetBits = static_cast<int>(ceil(log2(numSubnets)));

    int newCIDR = cidr + subnetBits;
    int maxHostsDEZ = 32 - newCIDR;
    int maxHosts = pow(2, maxHostsDEZ) - 2;

    int maxBitsForHosts = 32 - subnetBits;
    int subnetMaskBinary[31];
    int newSubnetMaskBinary[31];

    if (newCIDR <= maxBitsForHosts && numDevices <= maxHosts) {
        // Generate binary subnet mask for the original CIDR notation
        for (int i = 1; i <= cidr; i++) {
            subnetMaskBinary[i] = 1;
            if (i == 1) {
                cout << "Binary: ";
            }
            cout << subnetMaskBinary[i];

            if (i % 8 == 0 && i != 32) {
                cout << ".";
            }

            if (cidr == i) {
                // Fill remaining bits with 0 for subnet mask
                for (int z = cidr; z < 32; z++) {
                    subnetMaskBinary[z] = 0;
                    cout << subnetMaskBinary[z];
                }
                cout << endl;
            }
        }

        string newCIDRNotation = ipAddress + "/" + to_string(newCIDR);
        cout << "\nNew CIDR Notation: " << newCIDRNotation << endl;

        // Generate binary subnet mask for the new CIDR notation
        for (int i = 1; i <= newCIDR; i++) {
            newSubnetMaskBinary[i] = 1;
            if (i == 1) {
                cout << "Binary: ";
            }
            cout << newSubnetMaskBinary[i];

            if (i % 8 == 0 && i != 32) {
                cout << ".";
            }

            if (newCIDR == i) {
                // Fill remaining bits with 0 for subnet mask
                for (int o = newCIDR; o < 32; o++) {
                    newSubnetMaskBinary[o] = 0;
                    cout << newSubnetMaskBinary[o];
                }
                cout << endl;
            }
        }
        table(numSubnets, ipAddress, maxHosts);
    }
    else {
        cout << endl;
        cout << "This is not possible!" << endl;
    }
}

int main() {
    string ipAddress;
    int cidr;
    int numSubnets;
    int numDevices;

    cout << "Enter IP address: ";
    cin >> ipAddress;

    cout << "Enter CIDR notation: ";
    cin >> cidr;

    cout << "Enter number of subnets: ";
    cin >> numSubnets;

    cout << "Enter number of devices per subnet: ";
    cin >> numDevices;

    newCIDR(ipAddress, cidr, numSubnets, numDevices);
    return 0;
}
