using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using ProtoBuf;

public class MajiangInterface : MonoBehaviour {

    public GameObject mahjong_cube;
    public Transform my_pai_heap_place; //自己前面牌堆的初始位置
    public Transform opposite_pai_heap_place;   //对家前面牌堆的初始位置
    public Transform my_hand_pai_place; //自己手牌的初始位置
    public Transform opposite_hand_pai_place;   //对家手牌的初始位置
    public Transform my_out_pai_place; //自己出掉的牌放的位置
    public Transform opposite_out_pai_place;   //对家出掉的牌放的位置
    public Camera main_camera;
    public GameObject mouse_collider;   //用于触发鼠标事件的鼠标代替物体
    public GameObject show_text;    //显示文字
    //public GameObject del_button;

    private GameObject m_mouse; //鼠标
    private GameObject[] m_my_pai_heap; //自己跟前的牌堆
    private GameObject[] m_my_hand_pai; //自己手牌
    private int m_my_pai_heap_index;    //牌堆索引
    private GameObject[] m_opposite_pai_heap;   //对家跟前的牌堆
    private GameObject[] m_opposite_hand_pai; //对家手牌
    private byte[] m_pai_value;
    private int my_out_pai_num; //自己的出牌个数
    private int opposite_out_pai_num;   //对家的出牌个数

    // Use this for initialization
    void Start () {

        var platform = Application.platform;
        m_my_pai_heap = new GameObject[20]; 
        m_opposite_pai_heap = new GameObject[20];

        m_my_hand_pai = new GameObject[14];
        m_opposite_hand_pai = new GameObject[14];

        m_my_pai_heap_index = 20;
        //if (platform == RuntimePlatform.Android)
        Debug.LogFormat("current platform is {0}", platform);
        mahjong_cube.GetComponentInChildren<TextMesh>().text = "";
        m_mouse = Instantiate(mouse_collider, new Vector3(0, 0, 0), my_pai_heap_place.rotation) as GameObject;
        //初始化牌堆
        for (int i = 0; i < 10; i++)
        {

            Vector3 high = new Vector3(0, mahjong_cube.transform.localScale.y + (float)0.1, 0);   //高度
            Vector3 wide = new Vector3(0, 0, (mahjong_cube.transform.localScale.z + (float)0.05) * i  );   //宽度
            m_my_pai_heap[i * 2] = Instantiate(mahjong_cube, my_pai_heap_place.position + wide, my_pai_heap_place.rotation) as GameObject;   //底下一层
            m_my_pai_heap[i * 2 + 1] = Instantiate(mahjong_cube, my_pai_heap_place.position + wide + high, my_pai_heap_place.rotation) as GameObject;    //上面一层

            m_opposite_pai_heap[i * 2] = Instantiate(mahjong_cube, opposite_pai_heap_place.position + wide, opposite_pai_heap_place.rotation) as GameObject;   //底下一层
            m_opposite_pai_heap[i * 2 + 1] = Instantiate(mahjong_cube, opposite_pai_heap_place.position + wide + high, opposite_pai_heap_place.rotation) as GameObject;    //上面一层


        }

        ////初始化手牌
        //for (int i = 0; i < 13; i++)
        //{
        //    Vector3 wide = new Vector3(0, 0, (mahjong_cube.transform.localScale.z + (float)0.05) * i);   //宽度
        //    m_my_hand_pai[i] = Instantiate(mahjong_cube, my_hand_pai_place.position + wide, my_hand_pai_place.rotation) as GameObject;   //自己的手牌
        //    m_opposite_hand_pai[i] = Instantiate(mahjong_cube, opposite_hand_pai_place.position + wide, opposite_hand_pai_place.rotation) as GameObject;   //对家的手牌
        //}
    }
	
	// Update is called once per frame
	void Update () {

        //鼠标移动判定
        Ray ray = main_camera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit))
        {
            //Debug.LogFormat("ray is ready");
            if (hit.collider != null)
            {
                //Debug.LogFormat("ray is ready, name = {0}, pos=[{1}]", hit.collider.name, hit.transform.position);
                m_mouse.transform.position = hit.transform.position;

                //判断鼠标左键点击
                if (Input.GetMouseButtonDown(0))
                {
                    Debug.Log("Pressed left click.");
                    if (hit.collider.transform.GetComponent<cube_feature>() != null)    //表明这是牌
                    {
                        if (IsSubObjectExist(hit.collider.transform, m_my_hand_pai) == false)
                        {
                            Debug.Log("chosen cube is not belong my hand pai");
                            return;
                        }
                        Debug.Log("find cube script");
                        Vector3 wide = new Vector3(0, 0, (mahjong_cube.transform.localScale.z + (float)0.05) * my_out_pai_num);   //宽度
                        hit.collider.transform.rotation = my_pai_heap_place.rotation;
                        hit.collider.transform.GetComponent<cube_feature>().Move(my_out_pai_place.position + wide, 1);
                        my_out_pai_num++;
                    }
                }
            }
        }

        
    }

    //补牌
    void SupplyHandPai()
    {
        //销毁牌堆牌
        if (m_my_pai_heap[m_my_pai_heap_index] != null) 
        {
            Destroy(m_my_pai_heap[m_my_pai_heap_index]);
            m_my_pai_heap[m_my_pai_heap_index] = null;
            m_my_pai_heap_index--;
        }

        //手牌最右侧生成一张新牌
        Vector3 wide = new Vector3(0, 0, (mahjong_cube.transform.localScale.z + (float)0.05) * 12 + (float)0.2);   //宽度
        m_my_hand_pai[13] = Instantiate(mahjong_cube, my_hand_pai_place.position + wide, my_hand_pai_place.rotation) as GameObject;   //自己的手牌
    }

    public void ProcessGameData(byte[] buff, uint data_id)
    {
        System.IO.Stream stream = new System.IO.MemoryStream(buff);
        switch (data_id)
        {
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameBegin:
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameDealCards:
                {
                    bs.gameddz.deal_cards rsp = Serializer.Deserialize<bs.gameddz.deal_cards>(stream);
                    OnGameDealCards(rsp);
                }
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameTurnToPlayer:
                {
                    bs.gameddz.turn_to_player rsp = Serializer.Deserialize<bs.gameddz.turn_to_player>(stream);
                    OnGameTurnToPlayer(rsp);
                }
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameBidScore:
                
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameBidScoreEnd:
                {
                    bs.gameddz.bid_socre_end rsp = Serializer.Deserialize<bs.gameddz.bid_socre_end>(stream);
                    OnGameBidScoreEnd(rsp);
                }
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameOutCardsReq:
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameOutCardsReply:
                {
                    bs.gameddz.out_cards_reply rsp = Serializer.Deserialize<bs.gameddz.out_cards_reply>(stream);
                    OnGameOutCardsReply(rsp);
                }
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameSeenDataReq:
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameEnd:
                {
                    bs.gameddz.game_end rsp = Serializer.Deserialize<bs.gameddz.game_end>(stream);
                    OnGameEnd(rsp);
                }
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameDataReq:
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameSetAuto:
                {
                    bs.gameddz.set_auto rsp = Serializer.Deserialize<bs.gameddz.set_auto>(stream);
                    OnGameSetAuto(rsp);
                }
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameExpression:
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDGameScoreChage:
                break;
            case (uint)bs.gameddz.CMDID_Gameddz.IDCardsForRobots:
                break;
            default:
                break;
        }
    }

    public void OnGameDealCards(bs.gameddz.deal_cards rsp)
    {
        //初始化手牌
        for (int i = 0; i < 13; i++)
        {
            Vector3 wide = new Vector3(0, 0, (mahjong_cube.transform.localScale.z + (float)0.05) * i);   //宽度
            m_my_hand_pai[i] = Instantiate(mahjong_cube, my_hand_pai_place.position + wide, my_hand_pai_place.rotation) as GameObject;   //自己的手牌
            m_opposite_hand_pai[i] = Instantiate(mahjong_cube, opposite_hand_pai_place.position + wide, opposite_hand_pai_place.rotation) as GameObject;   //对家的手牌
        }


        m_pai_value = rsp.cards;


        int current_index = 0;  //用于计数
        for (int i = 0; i < m_pai_value.Length; i++)
        {
            if (m_pai_value[i] == 0 || m_pai_value[i] == 255)
            {
                continue;
            }

            int value = m_pai_value[i];
            string pai_text = value.ToString();
            m_my_hand_pai[current_index].GetComponentInChildren<TextMesh>().text = pai_text;
            current_index++;
            if (current_index >= 13)
            {
                break;
            }
        }

        
        
    }

    public void OnGameTurnToPlayer(bs.gameddz.turn_to_player rsp)
    {

    }

    public void OnGameBidScoreEnd(bs.gameddz.bid_socre_end rsp)
    {

    }

    public void OnGameOutCardsReply(bs.gameddz.out_cards_reply rsp)
    {

    }

    public void OnGameSetAuto(bs.gameddz.set_auto rsp)
    {

    }

    public void OnGameEnd(bs.gameddz.game_end rsp)
    {
        for (int i = 0; i < 14; i++)
        {
            Destroy(m_my_hand_pai[i]);
            Destroy(m_opposite_hand_pai[i]);

            show_text.GetComponent<Text>().text = "本局结束";
        }
    }

    //判断某个物体是否属于某组物体
    public bool IsSubObjectExist(Transform sub, GameObject[] array)
    {
        if (sub == null)
        {
            Debug.Log("IsSubObjectExist input param error");
            return false;
        }
        for (int i = 0; i < array.Length; i++)
        {
            if (array[i] == null)
            {
                Debug.Log("array element is null");
                return false;
            }
            if (sub == array[i].transform)
            {
                return true;
            }
        }
        return false;
    }
}
