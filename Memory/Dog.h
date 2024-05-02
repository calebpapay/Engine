
class Dog
{
public:
	//constructors
	Dog();
	Dog(int inA, int inB, int inC);
	Dog(const Dog &inDog);

	// assignment operator
	const Dog &operator = (const Dog &inDog);

	// destructor
	~Dog();

private:
	int a;
	int b;
	int c;
};

// ---  End of File ---------------
