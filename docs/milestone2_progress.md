# Milestone 2B

### Tasks and Timeline

The following sections describe our plan for the implementation of Milestone 2 that we have been following - the taks and the targeted internal deadlines (in GMT +8).

### Phase 1: Project Scaffolding (Internal Deadline: Saturday, Nov 14, midnight)

Task | Assignee
-----|---------
Skeleton class for Forward AD (implementing one function: addition) and example usage | Yuxin Ye
Unit tests and performance tests | Zeren Long
Doxygen integration | Aleksander Aleksiev
Packaging and distribution (update Makefile with shared object library creation) | Krithika Sundararajan

### Phase 2: Complete the implementation + docs (Internal Deadline: Wednesday, Nov 18, noon)
* Every member implements some functions, adds corresponding tests and documents the code in the Forward AD class.

Functions | Assignee
----------|---------
Multiplication, Division | Yuxin Ye
Subtraction, Power | Zeren Long
Exponential, Sine | Aleksander Aleksiev
Cosine, Tangent | Krithika Sundararajan

* Documentation: This will be updating the contents from the existing Milestone 1 doc, for the following sections.

Item | Assignee
-----|---------
How to use the package | Yuxin Ye
Software Organization | Aleksander Aleksiev
Implementation Details | Zeren Long
Future Features | Krithika Sundararajan


### Phase 3: Stretch goal (Internal Deadline: Thursday, Nov 19, midnight)

We will review the stretch goals and pick up one or more of the items below, once the main requirements for M2 are in place.
* Benchmark against other C++ libraries
* Creating DLL (Ref: https://stackoverflow.com/questions/16693273/how-do-i-create-a-library)
* UML diagrams for the documentation (Implementation Details)
* AD for Vector functions of Vector inputs

## Individual Progress Summary

### Aleksander Aleksiev
For M2, my main focus will be on setting up the inline code documentation tools (Doxygen) and making sure that any code we add is appropriately documented using these tools. This documentation will continue to be a focus of mine through the rest of the project. Since M1, I set up the skeleton framework, on which the M2 work was based.

### Krithika Sundararajan
For Milestone 2, my focus would be on setting up the packaging and distribution of our AD library, and I have been reading up on this and reviewing the lectures. As a basic step, this would involve defining a make target to create a shared object library that can be linked to the user’s application. As a stretch goal, I would also like to investigate distributing the library as a .dll. I am also attempting to create the package as a part of the CI in TravisCI, and publishing it to Github releases.

### Yuxin Ye
My focus for Milestone 2 is to organize the basic class structure for forward automatic differentiation, and meanwhile, implement and exemplify the `add` functionality. Since M1, I reviewed basic organizational knowledge needed to structure the project, including some features of C++11, tests, make, etc. And I also looked into some detailed implementations of neural networks for reference.

### Zeren Long
Since the submission of M1, I have done several surveys about automatic differentiation, including how famous AD frameworks, such as autodiff, autograd, implement the functionalities and how they design their project structure and API. My job for M2B is to write unit tests and performance tests for our M2 C++ forward mode demo. I plan to use Google test for this job, since it is one of the most popular testing frameworks for C++ projects.
