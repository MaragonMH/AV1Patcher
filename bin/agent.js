"use strict";
rpc.exports = {
    inject: (bootstrapper, assembly_path, type_name, method_name) => {
        const bootstrapperModule = Module.load(bootstrapper);
        const functionPointer = Module.getExportByName(bootstrapperModule.name, "bootstrapper_load_assembly");
        const bootstrapper_load_assembly = new NativeFunction(functionPointer, "void", ["pointer", "pointer", "pointer"], { exceptions: 'propagate' });
        const allocUtfString = Memory.allocUtf16String;
        bootstrapper_load_assembly(allocUtfString(assembly_path), allocUtfString(type_name), allocUtfString(method_name));
    },
};