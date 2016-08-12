using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class network : MonoBehaviour {

    // Update is called once per frame
    [DllImport("cpp_proto.dll", EntryPoint = "get_msg", CallingConvention = CallingConvention.Cdecl)]
    public extern static int get_msg(int a, int b);//与dll中一致 
    public void GetMsg() {
	
	}
}
