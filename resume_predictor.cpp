#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Step 1: Define structure to hold candidate info
struct Candidate {
    float gpa;
    int dsa_score;
    int projects;
    int internships;
    bool shortlisted;
};

// Step 2: Hardcoded mock dataset
vector<Candidate> dataset = {
    {8.5, 90, 3, 1, true},
    {7.2, 75, 2, 0, false},
    {9.1, 88, 4, 2, true},
    {6.8, 60, 1, 0, false},
    {8.9, 95, 5, 2, true},
    {7.0, 65, 2, 1, false},
    {9.3, 98, 5, 2, true},
    {6.5, 50, 1, 0, false},
    {8.0, 85, 3, 1, true},
    {7.5, 70, 2, 1, false}
};

// Step 3: Calculate probability based on soft matching logic
float calculateProbability(vector<Candidate>& data, float gpa, int dsa, int proj, int intern) {
    float totalScore = 0;
    int count = 0;

    for (auto& c : data) {
        if (c.shortlisted) {
            float score = 0;

            // Soft scoring: give partial credit for close matches
            if (abs(c.gpa - gpa) <= 1.0) score += 0.25;
            if (abs(c.dsa_score - dsa) <= 15) score += 0.25;
            if (abs(c.projects - proj) <= 2) score += 0.25;
            if (abs(c.internships - intern) <= 1) score += 0.25;

            totalScore += score;
            count++;
        }
    }

    if (count == 0) return 0.0;

    float avgScore = totalScore / count;
    if (avgScore > 1.0) avgScore = 1.0; // Clamp to max 100%

    return avgScore;
}

// Step 4: Main program to take user input and show prediction
int main() {
    float gpa;
    int dsa, proj, intern;

    cout << "=== Resume Screening Predictor ===" << endl;

    cout << "Enter GPA: ";
    cin >> gpa;
    cout << "Enter DSA Score (out of 100): ";
    cin >> dsa;
    cout << "Enter number of Projects: ";
    cin >> proj;
    cout << "Enter number of Internships: ";
    cin >> intern;

    float probability = calculateProbability(dataset, gpa, dsa, proj, intern);
    cout << "\n>> Chance of getting shortlisted: " << probability * 100 << "%" << endl;

    return 0;
}
