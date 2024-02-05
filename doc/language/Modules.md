# Modules

## Include

Add a single file module to the programm's set of sources.

```
#include "path/to/file.ltn"
```

## Import

Add a whole module folder to the programm's set of sources.

```
#import "path/to/directory"
```

The directory needs a file called `__module__.ltn` to be a valid module. This file may or may not contain code itself.  
It is advised to import any submodules inside the `__module__.ltn`-file.

## Duplicate files

If a file is added to the set of sources mutiple times it is filtered automatically on any subsequent inclusion.

## Roots

```
#import {"main"} "path/to/directory"
```