#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// To represent a single type of exercise
struct exercise {
    int id;
    string name;
    int minutes;
    int calories;
};

// The struct pick represents a picked exercise and how much of it is taken
struct pick {
    exercise* ex; // pointer to the original exericse
    double fraction; // 1.0 represents the full exercise while 0.5 is for half an exercise
};

// This function helps with sorting exercises by calories per minute for the greedy strategy
bool compare(exercise* a, exercise* b) {
    return double(a->calories) / a->minutes > double(b->calories) / b->minutes;
}

// This function uses greedy to take the exercises with the highest calories burned first.
// Half an exercise is also allowed at the end if it helps to fill the time
void greedy(vector<exercise>& group, int n) {
    // Makes sure that workout duration is between 15 and 120 mins
    if(n < 15 || n > 120) {
        cout << "Workout duration must be between 15 and 120 mins" << endl;
        return;
    }
    
    // Here we just build a list of pointers so that we can sort without moving the originals
    vector<exercise*> order;
    for(auto& i : group) {
        order.push_back(&i);
    }
    sort(order.begin(), order.end(), compare); // sorts by calories per minute in a descending manner
    
    int used = 0; // variable to track minutes used so far
    int totalCalories = 0; // tracks the total calories burned
    vector<pick> collect; // collects the picks
    
    // Here we go through the sorted list and fill the selected time
    for(auto& i : order) {
        // If we can take the exercise fully then we do it
        if(used + i->minutes <= n) {
            collect.push_back({i, 1.0});
            used+= i->minutes;
            totalCalories+= i->calories;
        } // Else, we check if we can take an exercise and if we can we take half
        else if(used < n && used+ i->minutes/2 <= n) {
            collect.push_back({i, 0.5});
            used += i->minutes/2;
            totalCalories += i->calories/2;
            break; // lastly we break so that we allow only one fractional exerise to fill what's left
        }
    }
    
    // prints the result
    cout << "Greedy: " << endl;
    cout << "Workout plan (name, minutes, calories): " << endl;
    for(auto& i: collect) {
        cout << i.ex->name << " (" << (i.ex->minutes * i.fraction) << "m, "
        << i.ex->calories *i.fraction << "cal)";
        if(i.fraction < 1.0) {
            cout << " (1/2)";
        }
        cout << endl;
    }
    cout << "Total Calories: " << totalCalories << " cal" << endl;
}

// finds the highest total burned calories with the constraint of a specific exercise group
// and time using dynamic programming
void dp(vector<exercise>& group, int n) {
    // Makes sure that workout duration is between 15 and 120 mins
    if(n < 15 || n > 120) {
        cout << "Workout duration must be between 15 and 120 mins" << endl;
        return;
    }
    
    int unit = n * 2; // we convert minutes to half minute units so halves can be integrated as integer steps
    
    // dp vector for storing highest calories
    vector<vector<double>> dp(group.size() + 1, vector<double>(unit + 1, 0.0));
    
    // we use this vector to make choices: if it equals 0 we skip, 1 we take fully, and 2 we take half
    vector<vector<int>> choice(group.size() + 1, vector<int>(unit + 1, 0));
    
    // loop for building the dp table
    for(int i = 1; i<= group.size(); i++) {
        int fullUnit = group[i-1].minutes * 2; // full exercise in half minute units
        int halfUnit = group[i-1].minutes; // half exercise in half minute units
        double fullCalories = group[i-1].calories; // full calories
        double halfCalories = fullCalories / 2.0; // half calories
        
        for(int j = 0; j <= unit; j++) {
            // this skips the exercise
            dp[i][j] = dp[i-1][j];
            choice[i][j] = 0;
            
            // if it fits, we try to take the full exercise
            if(j >= fullUnit) {
                double possible = dp[i-1][j-fullUnit] + fullCalories;
                if(possible > dp[i][j]) {
                    dp[i][j] = possible;
                    choice[i][j] = 1;
                }
            }
            
            // if it fits, we try to take half an exercise
            if(j >= halfUnit) {
                double possible = dp[i-1][j-halfUnit] + halfCalories;
                if(possible > dp[i][j]) {
                    dp[i][j] = possible;
                    choice[i][j] = 2;
                }
            }
        }
    }
    
    // here we use a stack to reconstruct the picks we made 
    stack<pick> s;
    double totalCalories = dp[group.size()][unit];
    for(int i = group.size(); i > 0; i--) {
        int c = choice[i][unit];
        if(c == 1) {
            s.push({&group[i-1], 1.0}); // took full exercise
            unit -= group[i-1].minutes * 2;
        } else if(c == 2) {
            s.push({&group[i-1], 0.5}); // took half an exercise
            unit -= group[i-1].minutes;
        }
    }
    
    // prints the result
    cout << "DP: " << endl;
    cout << "Workout plan (name, minutes, calories): " << endl;
    while(!s.empty()) {
        pick p = s.top();
        s.pop();
        cout << p.ex->name << " (" << p.ex->minutes * p.fraction << "m, " << p.ex->calories * p.fraction
        << "cal)";
        if(p.fraction < 1.0) {
            cout << " (1/2)";
        }
        cout << endl;
    }
    cout << "Total calories: " << totalCalories << " cal" << endl;
}

int main()
{
    // exercise groups
    vector<exercise> upper = {
        {0,"push ups", 10, 100},
        {1,"shoulder press", 15, 120},
        {2,"pull ups", 12, 110}
    };
    
    vector<exercise> lower = {
        {3,"squats", 10, 130},
        {4,"leg press", 8, 100},
        {5,"lunges", 20, 200}
    };
    
    vector<exercise> core = {
        {6,"sit ups", 15, 90},
        {7,"plank", 5, 70},
        {8,"russian twist",8,60}
    };
    
    vector<exercise> full = {
        {9,"jumping jacks", 10, 60},
        {10, "mountain climbs", 15, 110},
        {11,"burpees",20, 140}
    };
    
    // test trial using greedy and dp
    cout << "Test Trial 1" << endl;
    greedy(upper, 30);
    dp(upper, 30);

    // For min duration(greedy fails)
    cout << endl;
    cout << "Test trial 2: " << endl;
    greedy(upper,15);
    dp(upper,15);

    
    cout << endl;
    cout << "Test Trial 3: " << endl;
    greedy(core,40);
    dp(core,40);
}