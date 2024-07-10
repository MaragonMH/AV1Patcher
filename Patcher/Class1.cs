using HarmonyLib;
using System;
using System.Diagnostics;
using System.Reflection;

namespace Patcher
{
    public class Main
    {
        private static Harmony harmony;

        public static int InitializePatches(String s)
        {

            Console.WriteLine($"Patcher: Injected! {s}");

            Harmony.DEBUG = true;
            harmony = new Harmony("com.example.patch");

            // Uncomment unwanted
            // harmony.PatchAll(typeof(Main).Assembly);
            // harmony.PatchCategory("TestApp");
            harmony.PatchCategory("AV1");

            Console.WriteLine("Patcher: Happy");
            return 0;
        }
    }

    [HarmonyPatch]
    [HarmonyPatchCategory("TestApp")]
    public class TestAppPatches
    {
        static MethodBase TargetMethod()
        {
            return AccessTools.Method(AccessTools.TypeByName("TestApp.Program"), "F");
        }

        [HarmonyPrefix]
        static void F(ref int i)
        {
            i = 1337;
        }
    }

    [HarmonyPatch]
    [HarmonyPatchCategory("AV1")]
    public class AV1Patches
    {
        static MethodBase TargetMethod()
        {
            return AccessTools.Method(AccessTools.TypeByName("OuterBeyond.THTitleState"), "ColorLerp");
        }

        [HarmonyPrefix]
        static public bool ColorLerp(ref float __result, float beats, float startBeat)
        {
            Debug.WriteLine("Function: Running");
            __result = 100f;
            return true;
        }
    }
}

