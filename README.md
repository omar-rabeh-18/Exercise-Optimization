# Exercise-Optimization

## Overview
This project implements a feature for a workout app that recommends the most calorie-efficient workout plan based on user input. The user selects a target muscle group (upper, lower, core, full body) and a workout duration (between 15–120 minutes). The algorithm then returns the set of exercises (full or half) that maximizes calories burned.

## Features
- Choose a workout group and duration
- Returns highest-calorie workout plan
- Supports full or half exercises
- Two algorithmic strategies: Greedy and Dynamic Programming

## Algorithmic Approaches

### 1. Greedy
- Inspired by fractional knapsack
- Sorts exercises by calories/minute
- Fast (O(n log n)) and memory-efficient
- May not always produce optimal results

### 2. Dynamic Programming
- Guarantees optimal solution (0, ½, 1 selection)
- Time complexity: O(n × t)
- Slower but exact

## Sample Test Cases:
<img width="301" height="362" alt="Screenshot 2025-07-14 at 9 56 30 PM" src="https://github.com/user-attachments/assets/89a007b4-7e68-400c-ad36-99c4bb805091" />
I have attached an image showcasing three different test cases. The first test case shows greedy and dynamic programming achieving the same answer and also shows half an exercise included. The second test case shows a situation where greedy fails and dynamic programming finds a better answer that burns more calories. The third test case shows greedy and dynamic programming getting the same answer again but without half an exercise included in the result and a different exercise group being considered.

## Assumptions
- Workout duration must be between 15–120 mins
- No repetition of exercises
- Only full or half of an exercise can be selected
- Not designed for rest periods or cooldowns

## Developer Reflection
The idea was inspired by my own experience starting out in fitness and being overwhelmed by options. This feature simplifies that process by focusing on calorie-maximization and tailoring to user goals. I added half-exercise support based on instructor feedback to balance realism and algorithmic flexibility.

## Author
Omar Rabeh, Computer Engineering student  
