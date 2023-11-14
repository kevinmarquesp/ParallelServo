<!-- todo: list the dependencies -->
<!-- todo: add a todo list for the features -->

# ParallelServo | *Move multiple servos at the same time!* 🔥
This project meant to be a solution (unfortunatly, not a simple/easy solution)
to a problem at my school: Some projects that uses servo motors need to move
a bunch of them at the same time. Like I said, this library isn't very easy
to undersand — some knowlage of C++ will help, such as how classes and methods
work and how to use lambda functions —, but it's very useful and I think that
worth givint it a try; so, take a good look at the documentation and examples!

![Multiple Servo Handling Demo](docs/demo.gif)

## Documentation
### Warning
Whether you like it or not, this library was not precisely designed for
beginners in the development field. Therefore, understanding how this library
works and how to use it will depend on the developer experience that I assume
you already have; seek help from a teacher or experienced friend if you want
to use this library and, for some reason, cannot spare the time to fully
comprehend it. If you are the programmer who will explore this library, I
recommend that you just quickly skim through the documentation below and go
straight to the examples. Try running them on your machine and see what
happens by changing one thing or another — learn through practical experience.

### Public Methods
+ **`begin(pin, min, max)`**
    + This is the first function that you will use on your code. It will attach
      the servo object to the specified pin on the Arduino board, store the *min*
      and *max* values that the other methods will use to know when the movement
      should stop, and write the *min* value to the servo motor once it is
      attached. The parameters are as follows:
        + `pin`: The board pin that the servo object needs to be attached to.
          It must be a valid PWM pin, otherwise it will be ignored.
        + `min`: The minimum value that this servo can move to, in degrees. It
          must be between 0 and 180, otherwise it will be set to the default
          min value (0).
        + `max`: The maximum value that this servo can move to, in degrees. It
          must be between 0 and 180, otherwise it will be set to the default
          max value (180).
    + This function is essential to initialize the servo object and set its
      movement range. It should be called in the setup() function of your
      Arduino sketch. This function returns nothing.
+ **`move(deg, speed, condition)`**
    + This is the main function that you will use to move the servo object to a
      desired position with a given speed and a user-defined condition. The
      parameters are as follows:
        + `deg`: The target position that the servo should move to, in degrees.
          It must be between the min and max values of the servo, otherwise it
          will be ignored.
        + `speed`: The number of milliseconds that the servo should wait for
          each degree moved. It must be a positive value, otherwise it will be
          ignored.
        + `condition`: A boolean expression that will dictate if the servo
          should or should not start the move process. It can be any valid
          expression that evaluates to *true* or *false*, such as comparing the
          movement index with a certain value, checking the status of another
          servo, or using a button input. If the condition is true, the servo
          will move. If the condition is false, the servo will not move.
    + This function will do all the checks and conversions to see if the servo
      is ok to move and if the user condition is also true. If everything is
      valid, then it will pass those `deg` and `speed` values to the routine that
      counts the `millis()` and writes the position each interval. When the servo
      reaches the target position, it will mark itself as done and increment
      the *movement index* by one. This function returns a pointer to this servo
      object, so you can chain multiple `move()` calls in one line — take a look
      at the examples directory to better understand that concept.
+ **`move(deg, speed)`**
    + This is a wrapper for the previous function, it does the exact same thing,
      but the user condition is replaced by the statement: `this.getIndex() == 0`,
      which means that it will only move if the movement index is `0`, therefore,
      if it is the first movement that the servo should do before passing
      to the next ones. The parameters are as follows:
        + `deg`: The target position that the servo should move to, in degrees.
          It must be between the min and max values of the servo, otherwise it
          will be ignored.
        + `speed`: The number of milliseconds that the servo should wait for
          each degree moved. It must be a positive value, otherwise it will be
          ignored.
    + This function is useful when you want to create a simple sequence of
      movements, where each servo moves only once and waits for the previous
      one to finish. This function returns a pointer to this servo object, so
      you can chain multiple `move()` calls in one line.
+ **`reset()`**
    + This is a function that resets all the states of the servo object,
      including the movement counter (the *index*), the *lock* state, and the *done*
      state. It also writes the *min* value to the servo motor, so it goes back
      to the initial position. It is useful when you want to make a loop of
      movements or create a user input that resets the servo's state. This
      function returns nothing.
+ **`afterDone(routine())`**
    + This is a function that receives another function as a parameter (a.k.a:
      a lambda function) and only runs this function if this servo object is
      marked as done. It is used when you want to reset this servo's state,
      move another servo, or do any other action after the movement is
      completed.
+ **`getIndex()`**
    + This is a function that returns the current movement index of the servo
      object, which represents the number of movements that the servo has
      completed. It can be used to create conditions for the move() function,
      such as only move if the index is equal to a certain value.
+ **`isDone()`**
    + This is a function that returns true if the servo object is marked as
      done, which means that it has reached the target position and the
      movement index has been incremented. It can be used to check the status
      of the servo or to create loops of movements.
+ **`isLocked()`**
    + This is a function that returns true if the servo object is locked, which
      means that it cannot move until it is unlocked. It can be used to prevent
      unwanted movements or to synchronize multiple servos.
+ **`setLock(newState)`**
    + This is a function that sets the lock state of the servo object to the
      given boolean value. If the value is *true*, the servo will be locked and
      cannot move. If the value is *false*, the servo will be unlocked and can
      move normally. It can be used to control the movement of the servo
      manually or programmatically.
+ **`getPin()`**
    + This is a function that returns the pin number that the servo object is
      attached to. It can be used to identify the servo or to perform other
      operations on the pin.
+ **`getMin()`**
    + This is a function that returns the minimum value that the servo object
      can move to, as specified in the begin() function. It can be used to
      limit the movement range of the servo or to perform calculations on the
      position.
+ **`getMax()`**
    + This is a function that returns the maximum value that the servo object
      can move to, as specified in the begin() function. It can be used to
      limit the movement range of the servo or to perform calculations on the
      position.
+ **`getPos()`**
    + This is a function that returns the current position of the servo object,
      in degrees. It can be used to monitor the movement of the servo or to
      perform calculations on the position.

## Contributing
### Things To Be Done
+ [ ] On this README file, I need to add a section with the download links 
+ [ ] I also want to list the dependencies for both the user side and the developer side
+ [ ] Comment what is the objective of the `Scenes/Scenes.ino` example