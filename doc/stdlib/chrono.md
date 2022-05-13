### std::clock()
**Parameters**  

**Return value**  
Reference to a new Clock  

**Description**  
Creates a new Clock

---

### std::to_seconds(clock)
**Parameters**
* clock: A Clock

**Return value**  
Seconds as Float

**Description**  
Gets the passed time of the Clock since its creation

---

### std::to_milliseconds(clock)
**Parameters**
* clock: A Clock

**Return value**  
Milliseconds as Float

**Description**  
Gets the passed time of the Clock since its creation

---

### std::wait(seconds)
**Parameters**
* seconds: seconds as Int or Float

**Return value**  
null

**Description**  
Waits for a given amount of time.

---

### std::wait(seconds, clock)
**Parameters**
* seconds: seconds as Int or Float
* clock: a Clock

**Return value**  
null

**Description**  
Waits for a given amount of time. Uses passed Clock instead of a default constructed one.