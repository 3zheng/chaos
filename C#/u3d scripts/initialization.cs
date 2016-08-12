using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using ProtoBuf;
using System.Security.Cryptography;
using System;
using System.Text;

public class initialization : MonoBehaviour
{
    public GameObject show_text;
    public GameObject majiang_interface;

    public GameObject plan_id_input;
    public GameObject app_id_input;

    // Use this for initialization
    void Start()
    {
        Debug.LogFormat("net status ={0}", Middleware.status);
        Middleware.StartConnect();
        
    }

    // Update is called once per frame
    void Update()
    {
        int kind_id = 0, sub_id = 0, app_type = 0, app_id = 0;
        object msg = Middleware.RecvMessage(ref kind_id, ref sub_id, ref app_type, ref app_id);
        if (msg == null)
        {
            return;
        }
        switch (kind_id)
        {
            case (int)Middleware.EnumCommandKind.Client:
                switch (sub_id)
                {
                    case (int)bs.client.CMDID_Client.IDLoginRsp:    //登录回复
                        {
                            //bs.client.LoginRsp req = Serializer.Deserialize<bs.client.LoginRsp>(stream);
                            bs.client.LoginRsp rsp = (bs.client.LoginRsp)msg;
                            Debug.LogFormat("user_id={0}, result={1}", rsp.user_id, rsp.login_result);
                            if (rsp.login_result == bs.client.LoginRsp.Result.SUCCESS)
                            {
                                UserData.user_id = rsp.user_id;
                                show_text.GetComponent<Text>().text = "登录成功";
                            }
                        }
                        break;
                    default:
                        break;
                }

                break;
            case (int)Middleware.EnumCommandKind.HallClient:
                switch(sub_id)
                {
                    case (int)bs.hallclient.CMDID_HallClient.IDAllGroupRsp:
                        OnAllGroupRsp(msg, app_type, app_id);
                        break;
                    case (int)bs.hallclient.CMDID_HallClient.IDAllListRsp:
                        OnAllListRsp(msg, app_type, app_id);
                        break;
                    case (int)bs.hallclient.CMDID_HallClient.IDAllPlanRsp:
                        OnAllPlanRsp(msg, app_type, app_id);
                        break;
                    case (int)bs.hallclient.CMDID_HallClient.IDPlanAllStartPoint:
                        OnAllStarPointRsp(msg, app_type, app_id);
                        break;
                    case (int)bs.hallclient.CMDID_HallClient.IDGetMatchDetailRsp:
                        OnMatchDetailRsp(msg, app_type, app_id);
                        break;
                    default:
                        break;
                }
                break;
            case (int)Middleware.EnumCommandKind.Gate:
                switch (sub_id)
                {
                    case (int)bs.gate.CMDID_Gate.IDHelloRsp:    //
                        Debug.LogFormat("send loginreq");
                       // Middleware.status = 1;
                        SendLoginReq();
                        break;
                    default:
                        break;
                }

                break;

            case (int)Middleware.EnumCommandKind.MatchClient:
                switch(sub_id)
                {
                    case (int)bs.matchclient.CMDID_MatchClient.IDJoinRsp:   //报名回复
                        {
                            bs.matchclient.JoinRsp rsp = (bs.matchclient.JoinRsp)msg;
                            //UserData.PlanInfo info = new UserData.PlanInfo((int)rsp.plan_id);
                            Debug.LogFormat("receive joinrsp, result={0}", rsp.result);
                        }
                        break;
                    case (int)bs.matchclient.CMDID_MatchClient.IDMatchStart:    //开赛通知
                        {
                            bs.matchclient.MatchStart rsp = (bs.matchclient.MatchStart)msg;
                            UserData.enter_match.match_id = rsp.match_id;
                            UserData.enter_match.group_id = rsp.group_id;
                            UserData.enter_match.mp_appid = app_id;
                        }
                        break;
                    case (int)bs.matchclient.CMDID_MatchClient.IDEnterMatchRsp: //进入比赛通知
                        OnEnterMatchRsp(msg, app_type, app_id);
                        break;
                    case (int)bs.matchclient.CMDID_MatchClient.IDTableStatusInd:
                        {
                            bs.matchclient.TableStatus rsp = (bs.matchclient.TableStatus)msg;

                            UserData.enter_match.table_logic_appid = app_id;
                            UserData.enter_match.table_id = rsp.table_id;
                            //遍历users_rm，直到找到自己的座位号
                            for(int i = 0; i < rsp.users_rm.Count; i++)
                            {
                                if (rsp.users_rm[i].user_id == UserData.user_id)
                                {
                                    UserData.enter_match.seat_id = rsp.users_rm[i].seat_index;
                                }
                            }

                            //如果是拆桌，那么发送举手
                            if (rsp.table_stat == bs.matchclient.TableStatus.State.Dismiss)
                            {
                                SendPlayerActionReq(app_type, app_id);
                            }
                        }
                        break;
                    case (int)bs.matchclient.CMDID_MatchClient.IDGameData:
                        {
                            bs.matchclient.GameData data = (bs.matchclient.GameData)msg;

                            majiang_interface.GetComponent<MajiangInterface>().ProcessGameData(data.data, data.data_id);
                        }
                        
                        break;
                    default:
                        break;

                }
                break;


            default:
                break;
        }
    }

    void SendLoginReq()
    {
        bs.client.LoginReq req = new bs.client.LoginReq();

        req.game_kind = 501;
        req.action_type = bs.client.LoginReq.LoginAction.ByMobile;
        req.client_os = bs.client.LoginReq.ClientOS.Android;
        req.login_account = "91ytestno788";
        req.build_no = 4;
        req.market_id = 5;
        req.game_id = 6;
        //对密码进行md5加密
        //MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider();
        //byte[] testEncrypt = System.Text.Encoding.UTF8.GetBytes(test);
        //byte[] md5_bytes = md5.ComputeHash(testEncrypt);
        string test = "111111";
        req.login_password = GetStrMd5(test);
        req.client_version = "1.11";
        req.client_IP = "ok";     //客户端IP
        req.system_version = "未知版本";    //操作系统版本号
        req.bios_serial = "123456";       //BIOS序列号
        req.cpu_serial = "intel";        //CPU序列号
        req.HD_serial = "aaaa";     //硬盘序列号
        req.MAC_address = "HI-FE-09";       //MAC地址
        req.protect_data = "data";  //保护数据
        req.channel_id = 17;        //主渠道id
        req.site_id = 18;           //子渠道id
        req.bar_id = 19;            //网吧id
        req.GUID = "guid7719839";          //GUID
        req.logon_token = 21;		//登录令牌
        Middleware.SendMessage<bs.client.LoginReq>(req, (int)Middleware.EnumCommandKind.Client,
            (int)bs.client.CMDID_Client.IDLoginReq, (int)Middleware.EnumAppType.Login, (int)Middleware.EnumAppId.Send2AnyOne);   //
    }

    public void PressGetHallInfo()
    {
        Debug.LogFormat("发送获取all group请求");
        SendAllGroupReq(1, (int)Middleware.EnumAppId.Send2AnyOne);
    }

    public void SendAllGroupReq(int page_id, int app_id)
    {
        bs.hallclient.AllGroupReq req = new bs.hallclient.AllGroupReq();
        req.page_id = (uint)page_id;

        Middleware.SendMessage<bs.hallclient.AllGroupReq>(req, (int)Middleware.EnumCommandKind.HallClient,
            (int)bs.hallclient.CMDID_HallClient.IDAllGroupReq, (int)Middleware.EnumAppType.Gate, app_id);
    }

    public void PressJoinReq()
    {

        int count = plan_id_input.transform.childCount;
        //获得子对象
        var plan_child = plan_id_input.transform.FindChild("input_text");
        var app_child = app_id_input.transform.FindChild("input_text");
        if (plan_child != null && app_child != null)
        {
            int plan_id = Int32.Parse(plan_child.GetComponent<Text>().text);
            int app_id = Int32.Parse(app_child.GetComponent<Text>().text);
            SendJoinReq(plan_id, app_id);
        }
        
    }

    //
    //发送参赛报名请求
    //      
    public void SendJoinReq(int plan_id, int app_id)
    {
        bs.matchclient.JoinReq req = new bs.matchclient.JoinReq();
        int app_type = (int)Middleware.EnumAppType.Match;
        
                
        req.plan_id = (ulong)plan_id;
        req.match_id = 0;      
        req.is_cancel = false;

        Debug.LogFormat("发送报名请求,plan_id={0}, app_id={1}", plan_id, app_id);

        Middleware.SendMessage<bs.matchclient.JoinReq>(req, (int)Middleware.EnumCommandKind.MatchClient,
            (int)bs.matchclient.CMDID_MatchClient.IDJoinReq, app_type, app_id);
    }

    //发送进入比赛
    public void SendEnterMatchReq(bs.matchclient.MatchStart rsp, int app_type, int app_id)
    {

        bs.matchclient.EnterMatchReq req = new bs.matchclient.EnterMatchReq();
        req.match_id = rsp.match_id;
        req.match_group = rsp.group_id;
        req.enter_type = bs.matchclient.EnterMatchType.EnterMatch;
       
        Middleware.SendMessage<bs.matchclient.EnterMatchReq>(req, (int)Middleware.EnumCommandKind.MatchClient,
            (int)bs.matchclient.CMDID_MatchClient.IDEnterMatchReq, app_type, app_id);

    }

    //发送举手请求
    public void SendPlayerActionReq(int app_type, int app_id)
    {
        
        //开始找用户
        bs.matchclient.PlayerActionReq req = new bs.matchclient.PlayerActionReq();
        req.act_type = bs.matchclient.PlayerActionType.AT_SetReady;
        req.match_group = UserData.enter_match.group_id;
        req.match_id = UserData.enter_match.match_id;
        Middleware.SendMessage<bs.matchclient.PlayerActionReq>(req, (int)Middleware.EnumCommandKind.MatchClient,
            (int)bs.matchclient.CMDID_MatchClient.IDPlayerActionReq, app_type, app_id);

    }

    public static string GetStrMd5(string ConvertString)
    {
        MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider();
        string t2 = BitConverter.ToString(md5.ComputeHash(UTF8Encoding.Default.GetBytes(ConvertString)));
        t2 = t2.Replace("-", "");
        return t2;
    }

    void OnAllGroupRsp(object msg, int app_type, int app_id)
    {
        Debug.LogFormat("收到了all group回复");
        bs.hallclient.AllGroupRsp rsp = (bs.hallclient.AllGroupRsp)msg;

        for (int i = 0; i < rsp.items.Count; i++)
        {
            UserData.GroupInfo info = new UserData.GroupInfo();
            info.page_id = rsp.page_id;
            info.group_id = rsp.items[i].group_id;
            info.ver_code = rsp.ver_code;
            info.show_name = rsp.items[i].show_name;
            info.group_order = rsp.items[i].group_order;
            info.show_platform = rsp.items[i].show_platform;
            info.icon_index = rsp.items[i].icon_index;
            info.own_lists = new Dictionary<uint, UserData.ListInfo>();

            //插入元素
            if (UserData.hall_info.ContainsKey(info.group_id) == false)
            {
                UserData.hall_info.Add(info.group_id, info);
            }
            
        }
        
        
    }

    void OnAllListRsp(object msg, int app_type, int app_id)
    {
        Debug.LogFormat("收到了all list回复");
        bs.hallclient.AllListRsp rsp = (bs.hallclient.AllListRsp)msg;

        //先查找对应的group_id是否存在
        if (UserData.hall_info.ContainsKey(rsp.group_id))
        {
            for (int i = 0; i < rsp.items.Count; i++)
            {
                UserData.ListInfo info = new UserData.ListInfo();
                info.page_id = rsp.page_id;
                info.group_id = rsp.group_id;
                info.ver_code = rsp.ver_code;
                info.list_id = rsp.items[i].list_id;
                info.show_name = rsp.items[i].show_name;
                info.list_order = rsp.items[i].list_order;
                info.show_platform = rsp.items[i].show_platform;
                info.icon_index = rsp.items[i].icon_index;
                info.own_plans = new Dictionary<uint, UserData.PlanInfo>();

                //判断list_id是否存在
                if(UserData.hall_info[rsp.group_id].own_lists.ContainsKey(info.list_id) == false)
                {
                    UserData.hall_info[rsp.group_id].own_lists.Add(info.list_id, info);
                }
                //UserData.hall_info.Add(info);
            }
        }
        
    }

    void OnAllPlanRsp(object msg, int app_type, int app_id)
    {
        Debug.LogFormat("收到了all plan回复");
        bs.hallclient.AllPlanRsp rsp = (bs.hallclient.AllPlanRsp)msg;

        //先查找对应的group_id是否存在
        if (UserData.hall_info.ContainsKey(rsp.group_id))
        {
            //再查找list_id是否存在
            if (UserData.hall_info[rsp.group_id].own_lists.ContainsKey(rsp.list_id))
            {
                for (int i = 0; i < rsp.plan_ids.Count; i++)   //game_kind
                {
                    UserData.PlanInfo info = new UserData.PlanInfo();
                    info.page_id = rsp.page_id;
                    info.group_id = rsp.group_id;
                    info.ver_code = rsp.ver_code;
                    info.list_id = rsp.list_id;

                    info.plan_id = rsp.plan_ids[i];
                    info.plan_orders = rsp.plan_orders[i];
                    info.plan_show_nums = rsp.plan_show_nums[i];
                    info.game_kind = rsp.game_kind;
                }
            }
        }
    }

    void OnAllStarPointRsp(object msg, int app_type, int app_id)
    {

    }

    void OnMatchDetailRsp(object msg, int app_type, int app_id)
    {

    }

    void OnEnterMatchRsp(object msg, int app_type, int app_id)
    {
        
            bs.matchclient.EnterMatchRsp rsp = (bs.matchclient.EnterMatchRsp)msg;
            //记录下table_logic的app_id
            UserData.enter_match.table_logic_appid = (int)rsp.tablelogic_appid;

            //如果tableid不为0就是断线重连
            if (rsp.table_id != 0)
            {
                UserData.enter_match.table_id = rsp.table_id;
                //向match_phase发送

                bs.matchclient.BackGameReq back_req = new bs.matchclient.BackGameReq();
                int back_app_type = (int)Middleware.EnumAppType.TableLogic;
                int back_app_id = UserData.enter_match.table_logic_appid;

                back_req.group_id = UserData.enter_match.group_id;
                back_req.match_id = UserData.enter_match.match_id;
                back_req.table_id = UserData.enter_match.table_id;

                Middleware.SendMessage<bs.matchclient.BackGameReq>(back_req, (int)Middleware.EnumCommandKind.MatchClient,
                (int)bs.matchclient.CMDID_MatchClient.IDBackGameReq, back_app_type, back_app_id);
                //向table_logic发送
                //CMDGameddz_game_data_req game_data;
                bs.gameddz.game_data_req game_data = new bs.gameddz.game_data_req();

                //CMDMatchClient_GameData data_rsp;
                bs.matchclient.GameData data_req = new bs.matchclient.GameData();

                System.IO.MemoryStream stream = new System.IO.MemoryStream();
                Serializer.Serialize<bs.gameddz.game_data_req>(stream, game_data);
                byte[] buff = stream.ToArray();

                data_req.data = buff;

                //game_data.my_message_.SerializeToString(&data);

                data_req.data = buff;
                data_req.data_id = (int)bs.gameddz.CMDID_Gameddz.IDGameDataReq;
                data_req.game_kind = UserData.the_game_kind;

                Middleware.SendMessage<bs.matchclient.GameData>(data_req, (int)Middleware.EnumCommandKind.MatchClient,
                (int)bs.matchclient.CMDID_MatchClient.IDGameData, back_app_type, back_app_id);

                return;
            }

            if (bs.matchclient.EnterMatchRsp.EnterResult.OK != rsp.result_code)
            {
                //进入比赛失败的处理
            }
            SendPlayerActionReq(app_type, app_id);
        
    } 
}
