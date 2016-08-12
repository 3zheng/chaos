using UnityEngine;
using System.Collections;

public class cube_feature : MonoBehaviour {

    Transform m_cube_tran;
    Vector3 old_postion;

    private bool m_is_moving; //是否正在移动
    private Vector3 m_goal_position;  //移动的目标地址
    private int m_speed;    //移动的速度
    private int m_move_times;   //移动的次数
    private Vector3 m_per_distance; //一帧的移动距离

    // Use this for initialization
    void Start () {
    //    Debug.LogFormat("cube pos is {0}", transform.position);
        //因为C#分为值类型和引用类型，所以如果想记录初始位置，应该使用值类型Vector3，因为引用类型Transform会一直变动
        m_cube_tran = transform;
        old_postion = transform.position;
        m_is_moving = false;
    }
	
	// Update is called once per frame
	void Update () {
        
        if (m_is_moving)
        {
            if (m_speed * m_move_times < 100)
            {
                transform.position += m_per_distance;
            }
            else
            {
                transform.position = m_goal_position;
                m_is_moving = false;
            }
            m_move_times++;
        }
        
	}


    //进入触发器
    void OnTriggerEnter(Collider collider)
    {
//        Debug.LogFormat("enter trigger is {0}",collider.name);
        transform.position = new Vector3(transform.position.x, transform.position.y + transform.localScale.y, transform.position.z);
        
    }

    //离开触发器
    void OnTriggerExit(Collider collider)
    {
        if (!m_is_moving)
        {
//            Debug.LogFormat("exit trigger is {0}", collider.name);
            transform.position = old_postion;
        }
        
    }

    public void Move(Vector3 postion, int speed)
    {
        m_is_moving = true;
        m_goal_position = postion;
        m_speed = speed;
        m_move_times = 0;

        m_per_distance = (m_goal_position - transform.position) / 100 * m_speed;    //一帧的移动距离
    }
}

