# Advanced Programming - Parking Management System

## Project Overview
This project involves designing and implementing a parking management system that allows users to efficiently find, reserve, and check out parking spots based on predefined rules and pricing structures.

## Features
1. **Parking Spot Management**
   - Identification of available parking spots based on vehicle size.
   - Categorization of parking spots: `normal`, `covered`, `CCTV-monitored`.
   
2. **Vehicle Management**
   - Loading vehicle data from a CSV file.
   - Assigning vehicles to appropriate parking spots.
   
3. **Pricing and Cost Calculation**
   - Different pricing structures for each parking spot type.
   - Static price and additional daily charges based on parking type.
   
4. **Command-Line Interface**
   - Requesting a parking spot (`request_spot <Car’s name>`).
   - Assigning a spot (`assign_spot <Spot’s ID>`).
   - Checking out a vehicle (`checkout <Spot’s ID>`).
   - Advancing time (`pass_time <Number of days>`).
