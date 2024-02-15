# About Project

## ToDo Client

```
[] Add configurable cuda processing into project (frame should be a wrapper on mat and gpumat, processors should be created by factory which create different type of processors)
[] Export module should contain both data export to the local drive and data sending to the server (communication submodule?)
[] Reduce CPU using, without loosing app performance 
[X] Darkness compensation (another processor that only processes data when it's late?)
[] Builders and factories should contains settingsbuilder and path to settings instead of mainsettings ref
[X] VideoSource observer and observable 
[X] Multithreading (frame producer and consumer (Observer pattern?))
[X] Manager which connect all managers
[X] Refactoring AppClient constructor (connect with previous task?)
[X] Refactor data flow between all processors (mat copying and internal buffers)
[] DifferenceProcessor should use noise compensation during processing frame after low brightness compensation (settings with additional threshold?)
```

## ToDo Server
