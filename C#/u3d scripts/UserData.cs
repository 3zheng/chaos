using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public class UserData : MonoBehaviour {
    

    public class PlanInfo : IComparable
    {
        
        public bool is_joined;

        public uint page_id ;
        public uint  group_id ;         //大类
        public uint list_id ;           //小类
        public uint ver_code;

        public uint plan_id;    //设置的赛事id

        //赛事的显示顺序，对应于上面的顺序，这样做的原因，是为简化服务器的处理
        public uint plan_orders;
        //赛事的显示人数，对应于上面的顺序，这样做的原因，是为简化服务器的处理
        public uint plan_show_nums;

        public uint game_kind;  //对于手机类，请指定具体的游戏种类

        public int CompareTo(object right)  //list.Sort以后按照从小到大的顺序排
        {
            PlanInfo other = (PlanInfo)right;
            if (this.plan_orders > other.plan_orders)
            {
                return 1;
            }
            else if (this.plan_orders == other.plan_orders)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }
    }

    
    public class ListInfo : IComparable
    {
        public uint page_id;
        public uint group_id;
        public uint ver_code;

        public uint list_id;            //小类
        public string show_name;          //小类显示名称
        public uint list_order;         //显示顺序
        public uint show_platform;    //显示的平台
        public uint icon_index;      //显示的图标

        public Dictionary<uint, PlanInfo> own_plans;

        public int CompareTo(object right)
        {
            ListInfo other = (ListInfo)right;
            if (this.list_order > other.list_order)
            {
                return 1;
            }
            else if (this.list_order == other.list_order)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }
    }

    public class GroupInfo : IComparable
    {
        public uint page_id;
        public uint group_id;
        public uint ver_code;

        public string show_name;          //小类显示名称
        public uint group_order;         //显示顺序
        public uint show_platform;    //显示的平台
        public uint icon_index;      //显示的图标

        public Dictionary<uint, ListInfo> own_lists;

        public int CompareTo(object right)
        {
            GroupInfo other = (GroupInfo)right;
            if (this.group_order > other.group_order)
            {
                return 1;
            }
            else if (this.group_order == other.group_order)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }
    }

    public struct EnterMatchInfo
    {
        public ulong match_id;  //比赛id
        public ulong group_id;  //组别id
        public int mp_appid;    //阶段服务器id
        public int table_logic_appid;  //牌桌逻辑服务器id
        public ulong table_id;  //桌子id
        public uint seat_id;    //座位id
    }
    //专门存放公共数据的类

    //比赛类型
    public static uint the_game_kind = 501;
    //大厅赛事信息
    public static Dictionary<int, PlanInfo> show_plans; 
    //已参加的比赛的信息
    public static EnterMatchInfo enter_match;   
    //用户id
    public static ulong user_id;

    public static Dictionary<uint, GroupInfo> hall_info;    //大厅的信息
    
}
