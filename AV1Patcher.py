import frida
import subprocess

# COMPILE IN x64 FOR .NET FRAMEWORK 4.0
# COMPILE IN x86 FOR .NET FRAMEWORK 4.5+
# EXPERIMENT IF YOU GET LOAD MODULE ERROR (0x1c) IN FRIDA

def process_exists(process_name):
    progs = str(subprocess.check_output('tasklist'))
    if process_name in progs: return True
    else: return False

print ("Main: Starting App")

# Uncomment unwanted
process = "TestApp.exe" # x86
process = "TestApp4.exe" # x64
process = "AxiomVerge.exe" # x86

if not process_exists(process):
    subprocess.Popen([process])
    
session = frida.attach(process)
    
print ("Main: Loading App")
with open('agent.js', 'r') as file:
    script = session.create_script(file.read())  
    script.load()
    script.exports_sync.inject("Bootloader.dll", "Patcher.dll", "Patcher.Main", "InitializePatches");
    script.unload();

print ("Main: Finished")

