CREATE TABLE [dbo].[zone_plan_def]
(
	[plan_id] INT NOT NULL, 
    [show_state] INT NOT NULL DEFAULT 1, 
    [modify_time] DATETIME NULL DEFAULT getdate(), 
    [show_order] INT NOT NULL DEFAULT 1, 
    [plan_type] INT NOT NULL DEFAULT 1, 
    [show_platform] INT NOT NULL DEFAULT 0x0f, 
    [is_title_match] INT NOT NULL DEFAULT 1, 
    CONSTRAINT [PK_zone_match_plan] PRIMARY KEY ([plan_id]), 
    --CONSTRAINT [CK_zone_match_plan_Column] unique([plan_id],[parent_list_id])
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛事的显示，赛区最小的元素，与自由赛和锦标赛的表相关，plan_id也不是表内自增的，而是去关联自由赛和锦标赛的赛事详情表的id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_def',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'状态 0无效 1有效',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_def',
    @level2type = N'COLUMN',
    @level2name = 'show_state'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'创建或者更新时间',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_def',
    @level2type = N'COLUMN',
    @level2name = 'modify_time'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示顺序',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_def',
    @level2type = N'COLUMN',
    @level2name = N'show_order'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'=1 表示这是固定类，所有的客户端都显示的 =2表示网吧类，根据IP显示 =3表示版本类，只显示给某个特定的版本',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_def',
    @level2type = N'COLUMN',
    @level2name = N'plan_type'
GO

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示的平台 &0x01=PC平台 &0x02=IOS平台显示 &0x04=android平台 &0x08预留',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_def',
    @level2type = N'COLUMN',
    @level2name = N'show_platform'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'是否为比赛（锦标赛）类型  1是  0否',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_def',
    @level2type = N'COLUMN',
    @level2name = N'is_title_match'