using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using ProtoBuf;

public class Middleware  {

    public enum EnumCommandKind
    {
        
            NullType = 0,
            RPC = 1,                       ///RPC 回调
            LambdaFunction = 5,           ///Lambda函数调用  
            Defines = 6,                  ///基本定义
            System = 7,                   ///系统 
            Logger = 8,                   ///日志

            NetWork = 9,                ///网络
            Router = 10,                ///路由类 
            AppFrame = 11,              ///App之间交互的一些通用报文，简化设计
            Gate = 12,                  ///Gate
            Client = 13,                ///客户端类
            MatchClient = 14,           ///match客户端类
            MCMS = 15,                    /// mc与ms之间的交互
            TableLogic = 16,              /// mp与TableLogic之间的交互 
            Fund = 17,                        //财富类
            HallClient = 18,                  //大厅客户端类
            MatchPhase = 19,                //比赛过程大类
            RankList = 20,                  //比赛排名大类
            List = 21,
            MatchDB = 22,

            PrivateInternal = 0x100,      // 内部私有
            PrivateBegin = 0x101,         // 私有开始
            PrivateEnd = 0x110,           // 私有结束
            GameStart = 0x120,            // 开始具体游戏
            Game = 0x120,                 // 开始具体游戏
            Last = 0x0FFE,                //最后一个4095

    };

    public enum EnumAppType
    {
        
            All = 1,        //所有，这个ALL表示
            Random = 2, //不指定服务器id，发往任意空闲的APP

            Gate = 5,       //网关
            Router = 6,     //中继器
            Login = 7,          //登录管理
            Online = 8,     //在线管理
            Fund = 9,           //财富
            List = 10,          //列表
            Connect_To_Center = 11,     //与中心服务器的接口

            FreeMatch = 12,     //自由赛
            Match = 13,         //锦标赛
            TableLogic = 14,    //牌桌逻辑
            MatchPhase = 15,     //比赛流程
            RankList = 16,      //排名列表

            MatchDB = 18,           //比赛DB

            Conect_To_Gold = 19,    //金币处理服务器

            Tool = 0xE0,    //工具
            Last = 0xFE,                 //目前250+种app类型肯定ok.
        
    };


    public enum EnumAppId
    {
        
            Send2All = 1,   //发送到所有
            Send2AnyOne = 2,    //发送到随意任意一个
        
    };

    public static int status = 0;   //判断网络状态

    [DllImport("network", EntryPoint = "StartConnection")]
    private extern static void StartConnection();//与dll中一致 

    [DllImport("network", EntryPoint = "GetMsgBuffSize")]
    private extern static int GetMsgBuffSize(ref int kind_id);//与dll中一致 

    [DllImport("network", EntryPoint = "GetMsgBuff")]
    private extern static int GetMsgBuff(byte[] buff, ref int kind_id, ref int sub_id);//与dll中一致 

    [DllImport("network", EntryPoint = "SendMsgBuff")]
    private extern static int SendMsgBuff(byte[] buff, int size, int kind_id, int sub_id, int app_type, int app_id);//与dll中一致 

    [DllImport("network", EntryPoint = "IsEncodeReady")]
    private extern static bool IsEncodeReady();//与dll中一致 

    public static void StartConnect()
    {
        bool ret = IsEncodeReady();
        if (!ret)    //如果网络没准备好开始连接
        {
            StartConnection();
        }
    }

    public static object RecvMessage(ref int kind_id, ref int sub_id, ref int app_type, ref int app_id)
    {

        int check_kind_id = 0;
        int size = GetMsgBuffSize(ref check_kind_id);
        if (0 == size && 0 == check_kind_id)  //因为还有像hellorsp这样的没有报文长度但是有返回的报文，不能只靠size是否为0来判断
        {
            return null;
        }
        byte[] buff = new byte[size];
        //int kind_id = 0;
        GetMsgBuff(buff, ref kind_id, ref sub_id);

        System.IO.Stream stream = new System.IO.MemoryStream(buff);

        switch(kind_id)
        {

            case (int)Middleware.EnumCommandKind.HallClient:
                switch (sub_id)
                {
                    case (int)bs.hallclient.CMDID_HallClient.IDAllGroupRsp:
                        {
                            bs.hallclient.AllGroupRsp req = Serializer.Deserialize<bs.hallclient.AllGroupRsp>(stream);
                            return req;
                        }
                    case (int)bs.hallclient.CMDID_HallClient.IDAllListRsp:
                        {
                            bs.hallclient.AllListRsp req = Serializer.Deserialize<bs.hallclient.AllListRsp>(stream);
                            return req;
                        }
                    case (int)bs.hallclient.CMDID_HallClient.IDAllPlanRsp:
                        {
                            bs.hallclient.AllPlanRsp req = Serializer.Deserialize<bs.hallclient.AllPlanRsp>(stream);
                            return req;
                        }
                    case (int)bs.hallclient.CMDID_HallClient.IDPlanAllStartPoint:
                        {
                            bs.hallclient.PlanAllStartPoint req = Serializer.Deserialize<bs.hallclient.PlanAllStartPoint>(stream);
                            return req;
                        }
                    case (int)bs.hallclient.CMDID_HallClient.IDGetMatchDetailRsp:
                        {
                            bs.hallclient.GetMatchDetailRsp req = Serializer.Deserialize<bs.hallclient.GetMatchDetailRsp>(stream);
                            return req;
                        }
                    default:
                        break;
                }
                break;
            case (int)EnumCommandKind.Client:
                switch(sub_id)
                {
                    case (int)bs.client.CMDID_Client.IDLoginRsp:
                        {
                            bs.client.LoginRsp req = Serializer.Deserialize<bs.client.LoginRsp>(stream);
                            return req;
                        }
                        
                    default:
                        break;
                }
                break;
            case (int)EnumCommandKind.Gate:
                switch(sub_id)
                {
                    case (int)bs.gate.CMDID_Gate.IDHelloRsp:
                        {
                            bs.gate.HelloRsp req = new bs.gate.HelloRsp();
                            Debug.LogFormat("get hellorsp");
                            return req;
                        }

                    default:
                        break;
                }
                break;
            case (int)Middleware.EnumCommandKind.MatchClient:
                switch (sub_id)
                {
                    case (int)bs.matchclient.CMDID_MatchClient.IDJoinRsp:   //报名回复
                        {
                            bs.matchclient.JoinRsp req = Serializer.Deserialize<bs.matchclient.JoinRsp>(stream);
                            return req;
                        }
                        
                    case (int)bs.matchclient.CMDID_MatchClient.IDMatchStart:    //开赛通知
                        {
                            bs.matchclient.MatchStart req = Serializer.Deserialize<bs.matchclient.MatchStart>(stream);
                            return req;
                        }
                        
                    case (int)bs.matchclient.CMDID_MatchClient.IDEnterMatchRsp: //进入比赛通知
                        {
                            bs.matchclient.EnterMatchRsp req = Serializer.Deserialize<bs.matchclient.EnterMatchRsp>(stream);
                            return req;
                        }
                        
                    case (int)bs.matchclient.CMDID_MatchClient.IDTableStatusInd:
                        {
                            bs.matchclient.TableStatus req = Serializer.Deserialize<bs.matchclient.TableStatus>(stream);
                            return req;
                        }
                        
                    case (int)bs.matchclient.CMDID_MatchClient.IDGameData:
                        {
                            bs.matchclient.GameData req = Serializer.Deserialize<bs.matchclient.GameData>(stream);
                            return req;
                        }

                    default:
                        break;

                }
                break;
            default:
                break;
        }

        return null;
    }

    

    public static void SendMessage<T>(T msg, int kind_id, int sub_id, int app_type, int app_id)
    {
        bool ret = IsEncodeReady();
        if (!ret)    //如果网络没准备不发送消息
        {
            return;
        }
        System.IO.MemoryStream stream = new System.IO.MemoryStream();
        Serializer.Serialize<T>(stream, msg);
        byte[] buff = stream.ToArray();
        
        SendMsgBuff(buff, buff.Length, kind_id, sub_id, app_type, app_id);
    }
}
