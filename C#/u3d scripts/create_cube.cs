using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Runtime.InteropServices;


public class create_cube : MonoBehaviour {

    public GameObject mahjong_cube;
    public Transform init_place;
    public Camera main_camera;
    public GameObject mouse_collider;
    public GameObject del_button;

    private GameObject m_mouse_btn;
    private GameObject[] m_all_cube;

    private int m_index;  //

    //
    // Use this for initialization
    [DllImport("cpp_proto.dll", EntryPoint = "get_msg", CallingConvention = CallingConvention.Cdecl)]
    public extern static int get_msg(byte[] buff, ref int length);//与dll中一致 

    void Start () {

        var platform = Application.platform;
        m_all_cube = new GameObject[20];
        m_index = 0;
        //if (platform == RuntimePlatform.Android)
        Debug.LogFormat("current platform is {0}", platform);
        mahjong_cube.GetComponentInChildren<TextMesh>().text = "";
        m_mouse_btn = Instantiate(mouse_collider, new Vector3(0,0,0), init_place.rotation) as GameObject;
        for (int i = 0; i < 10; i++)
        {
            
            Vector3 high = new Vector3(0, mahjong_cube.transform.localScale.y + (float)0.1, 0);   //高度
            Vector3 wide = new Vector3(0, 0, mahjong_cube.transform.localScale.z * i + (float)0.1);   //宽度
            m_all_cube[i * 2] = Instantiate(mahjong_cube, init_place.position + wide, init_place.rotation) as GameObject;
            m_all_cube[i * 2 + 1] = Instantiate(mahjong_cube, init_place.position + wide + high, init_place.rotation) as GameObject;
            
        }
        
	}
	
	// Update is called once per frame
	void Update () {
        
        //var platform = Application.platform;

        //var btn_pos = Input.mousePosition;
        //var world_pos = main_camera.ScreenToWorldPoint(Input.mousePosition);
        //Debug.LogFormat("mouse pos is x={0}, y={1}, z={2}", Input.mousePosition.x, Input.mousePosition.y, Input.mousePosition.z);
        //Debug.LogFormat("world_pos is x={0}, y={1}, z={2}", world_pos.x, world_pos.y, world_pos.z);
        Ray ray = main_camera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit))
        {
            //Debug.LogFormat("ray is ready");
            if (hit.collider != null)
            {
                //Debug.LogFormat("ray is ready, name = {0}, pos=[{1}]", hit.collider.name, hit.transform.position);
                m_mouse_btn.transform.position = hit.transform.position;
            }
        }
            
        //Debug.LogFormat("current platform is {0}", platform);
    }

    public void MyDestroyCube()
    {
        if (20 == m_index)
        {
            del_button.SetActive(false);
            return;
        }

        if (m_all_cube[m_index] != null)
        {
            Destroy(m_all_cube[m_index], (float)0.05);
            //if (m_index < 5)
            //{
            //    m_all_cube[m_index].GetComponent<Renderer>().enabled = false;   //物体不渲染，但是物体仍然存在于场景中仍然会有物理效果
            //}
            //else
            //{
            //    Destroy(m_all_cube[m_index], (float)0.05);
            //}
            
            m_index++;
        }
        
        
    }

    public void RepairButton()
    {
        
        for (int i = 0; i < 10; i++)
        {
            if (m_all_cube[i] != null)
            {
                m_all_cube[i].GetComponent<Renderer>().enabled = true;   //物体不渲染，但是物体仍然存在于场景中仍然会有物理效果
            }
            
        }
        //del_button.active = true;
        del_button.SetActive(true);
        int count = del_button.transform.childCount;
        Debug.LogFormat("childcount = {0}", count);
        //获得子对象
        for (int i = 0; i < count; i++)
        {
            if (del_button.transform.GetChild(i))
            {
                Debug.LogFormat("get child = {0}", del_button.transform.GetChild(i).name);
                
                if (del_button.transform.GetChild(i).GetComponent<Text>() != null)
                {
                    Debug.LogFormat("get text");

                    del_button.transform.GetChild(i).GetComponent<Text>().text = "删除按键";

                    byte[] my_buff = new byte[100000];
                    int size = 0;
                    int result = get_msg(my_buff, ref size);
                    string showtext = "删除按键";
                    byte[] byteArray = System.Text.Encoding.Default.GetBytes(showtext);
                    
                    Debug.LogFormat("show byte size = {0}", byteArray.Length);
                }
            }
        }
        //GetComponentInChildren<GUIText>()
        for (int i = 0; i < 10; i++)
        {

            Vector3 high = new Vector3(0, mahjong_cube.transform.localScale.y + (float)0.1, 0);   //高度
            Vector3 wide = new Vector3(0, 0, mahjong_cube.transform.localScale.z * i + (float)0.1);   //宽度
            m_all_cube[i * 2] = Instantiate(mahjong_cube, init_place.position + wide, init_place.rotation) as GameObject;
            m_all_cube[i * 2 + 1] = Instantiate(mahjong_cube, init_place.position + wide + high, init_place.rotation) as GameObject;

        }
        m_index = 0;
    }
}
