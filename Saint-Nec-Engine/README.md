To check test easily can create a bash file in the /build (here it is for /build/Saint-Nec-Engine). It helps when we are working on graphics component to ensure the update didn't break some rules:

```bash
#!/bin/bash
cd ../Saint-Nec-Engine-Test
make -j
./testInteraction
./testManager 
./testBoxCollider 
./testCollision 
./testSphereCollider
cd -
```

Do not forget to chmod +x file.sh
To execute you just need to : ./file.sh