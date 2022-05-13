### std::random::mersenne()
since 1.3  
**Parameters**  

**Return value**  
RandomEngine  

**Description**  
Creates a new mersenne twister RandomEngine. The engine is initilized with a random seed.

--- 

### std::random::mersenne(seed)
since 1.3  
**Parameters**  
* seed: Int

**Return value**  
RandomEngine  

**Description**  
Creates a new mersenne twister RandomEngine. The engine is initilized with a the passed seed.

--- 

### std::random::rand(rng)
since 1.3  
**Parameters**  
* rng: RandomEngine

**Return value**  
Int  

**Description**  
Generates a random 64-Bit integer 

--- 

### std::random::rand:int(rng, min, max)
since 1.3  
**Parameters**  
* rng: RandomEngine
* min: Int
* max: Int

**Return value**  
Int  

**Description**  
Generates a random integer between min and max

--- 

### std::random::rand_float(rng, min, max)
since 1.3  
**Parameters**  
* rng: RandomEngine
* min: Float
* max: Float

**Return value**  
Float  

**Description**  
Generates a random float between min and max

--- 

### std::random::decision(rng, min, max)
since 1.3  
**Parameters**  
* rng: RandomEngine
* p: propability

**Return value**  
Bool  

**Description**  
Generates a random Bool. "p" is the proabilty of the return value being true.

--- 

### std::random::split(rng)
since 1.3  
**Parameters**  
* rng: RandomEngine

**Return value**  
RandomEngine  

**Description**  
Creates a new RandomEngine of the same type as "rng" and uses "rng" to seed the new engine. 