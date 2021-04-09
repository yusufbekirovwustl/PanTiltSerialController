# PanTiltSerialController
Software Written for a Serial Interface to Two Servos connected to pca9685

Overview
--------
•	main – main driver for the program.
  o	Starts serial, wiringPi, and server driver.
  o	Creates, initializes, and deletes objects for InputParser, AbstractCommand derived objects,
    CoordinateCommander, StateSnapshot, State, and PWMController.
  o	Adds AbstractCommand derived object values into InputParser’s map of name keys.
  
•	InputParser – Parses commands from serial port and calls correct derived class of AbstractCommand 
                with arguments
  o	Adds Commands to map of AbstractCommands to extend types of commands
  o	Uses loop to continuously prompt the user for input
  o	Can list supported commands with ‘help’ command supported by default
  o	Can quit the application with ‘q’ command supported by default
  
•	AbstractCommand (interface) – An abstract interface to supported command types, has default destructor, 
                                an execute() command with a string input to execute the command with the 
                                string input as parameters, and displayInfo to display info about command 
                                usage, each derived class has pointer to CoordinateCommander object, essentially
                                a more finely-tuned parser for a specific command type
                                 
  o	PanCommand – A derived class of AbstractCommand, when ‘pan’ is executed with arguments ‘left’,’right’,’up’,’down’ 
                 moves the top plate of pan/tilt platform in the argument’s direction 1/10 of maximum range.
  o	SaveCommand – A derived class of AbstractCommand, when ‘pan’ is executed with an argument for a name, a StateSnapshot 
                  from the current State is saved as value in a map with the name as key within the CoordinateCommander object
  o	LoadCommand – A derived class of AbstractCommand, when ‘load’ is executed with an argument for a name, the StateSnapshot from 
                  a map with the name as key within the CoordinateCommander object is loaded if it was saved beforehand
  o	ViewCommand – A derived class of AbstractCommand, when ‘view’ is executed with no arguments, the name keys within the map of 
                  StateSnapshots pointer values inside the CoordinateCommander object is displayed
  o	DeleteCommand – A derived class of AbstractCommand, when ‘delete’ is executed with an argument for a name,the StateSnapshot 
                    from a map with the name as key within the CoordinateCommander object is deleted if it was saved beforehand
  o	SetCommand – A derived class of AbstractCommand, when ‘set’ is executed with two arguments of floats between 0 and 1, a StateSnapshot
                 is created with argument parameters and is loaded

•	CoordinateCommander – Handles the functionality between derived AbstractCommands and StateSnapshots, Can save, load, view, set, and delete
                        StateSnapshot Objects (needs access to State object to create StateSnapshot), uses StateSnapshot objects to change State
                        
•	StateSnapshot – A ‘copy’ of the State object, needs access to State object to change its contents, uses ‘restoreOne’ function and ‘restoreTwo’ 
                  function to restore its ‘state’ onto the State object
                  
•	State – The current ‘state’ of the Servo modules, can use ‘setOne’ function  and ‘setTwo’ functionto call PWMController to change servo position 
          (needs access to a PWMCOntroller object to use ‘setOne’ function and ‘setTwo’ function, has a ‘createStateSnapshot’ function that returns 
          a StateSnapshot object based on its current internal values( a copy of the current state)
          
•	PWMController – Uses PCA9685 driver to write to servos using ‘pwmWritePercentage’ function and gives current servo value using ‘getPin’ function, 
                  used similar style used in the PCA9685 driver examples. Uses concept of ‘millis’ to calculate the amount of total time to raise signal 
                  for a certain position of servo for a pwm signal.

