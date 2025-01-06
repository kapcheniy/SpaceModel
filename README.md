# SpaceModel
Space Simulation Model
This Qt application is designed to simulate a space model with stars and planets. The user can interact with the simulation by adding celestial bodies, controlling the simulation's speed, and adjusting the simulation's view mode. The program allows the user to control the simulation through various menu options.

Features
File Menu:

Открыть: Open a previously saved simulation file.
Сохранить: Save the current simulation state.
View Menu:

Полноэкранный режим: Toggle fullscreen mode.
Оконный режим: Toggle windowed mode.
Simulation Menu:

Построить модель: Start the simulation.
Пауза: Pause the simulation.
Продолжить: Continue the paused simulation.
Сбросить модель: Stop the simulation and reset the model.
Add Menu:

Звезда: Add a star to the simulation.
Планету: Add a planet to the simulation.
Simulation Speed Menu:

Choose between different speeds for the simulation:
0.25x
0.5x
1x
1.5x
2x
Help Menu:

О программе: Display information about the program.
Requirements
Qt 5 or higher
C++ compiler

Building the Project
Clone this repository:
->  git clone <repository-url>

Navigate to the project directory:
->  cd <project-directory>

Open the project with Qt Creator or use the following commands to build the project:

For Linux/macOS:
->  qmake && make

For Windows (using Visual Studio):
->  qmake && nmake
Running the Application

Once the project is built, you can run the application by executing the generated executable file. For example:

On Linux/macOS:
->  ./SpaceSimulation

On Windows:
->  SpaceSimulation.exe
