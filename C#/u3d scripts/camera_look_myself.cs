using UnityEngine;
using System.Collections;

public class camera_look_myself : MonoBehaviour {

    public Transform middle;    //中途的位置
    public Transform goal;  //目标位置
    public int speed;
    
    private float total = (float)0;
    private Vector3 D_value;    //Transform差值

    void Start()
    {
        D_value = new Vector3(middle.rotation.x - transform.rotation.x, middle.rotation.y - transform.rotation.y, middle.rotation.z - transform.rotation.z) / 10;
    }

    // Update is called once per frame
    void Update () {

        //transform.LookAt(goal);
        //以x轴为条件
        var wantedRotation = Quaternion.FromToRotation(transform.position, middle.position);
        var t = speed / Quaternion.Angle(transform.rotation, wantedRotation) * Time.deltaTime;
        var q = Quaternion.Slerp(transform.rotation, middle.rotation, t);
        transform.rotation = q;

        //Debug.LogFormat("goal is [{0},{1},{2}]", goal.position.x, goal.position.y, goal.position.z);
        /*
        Debug.LogFormat("transform.rotation.x is {0}, middle.rotation.x is {1}", transform.rotation.x, middle.rotation.x);
            Debug.LogFormat("D_value is [{0},{1},{2}]", D_value.x, D_value.y, D_value.z);
            transform.Rotate(D_value * speed);
            total = D_value.x * speed + total;
            Debug.LogFormat("total is {0}", total);
        */

    }
}
