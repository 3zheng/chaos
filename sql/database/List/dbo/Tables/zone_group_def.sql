CREATE TABLE [dbo].[zone_group_def]
(
	[group_id] INT NOT NULL identity(1,1) PRIMARY KEY, 
    [group_name] NVARCHAR(50) NOT NULL, 
    [group_type] INT NOT NULL DEFAULT 1, 
    [group_type_att_data] INT NULL, 
    [show_order] INT NOT NULL DEFAULT 1, 
    [show_platform] INT NOT NULL DEFAULT 0x0f, 
    [create_time] DATETIME NOT NULL DEFAULT getdate(), 
    [show_state] INT NULL DEFAULT 1 
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛区第二层级，就是左侧标签页【组】,page_id和group_id是一对多的关系',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_group_def',
    @level2type = NULL,
    @level2name = NULL
GO

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'【组】名',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_group_def',
    @level2type = N'COLUMN',
    @level2name = N'group_name'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'=1 表示这是固定类，所有的客户端都显示的 =2表示网吧类，根据IP显示 =3表示渠道类，只显示给某个特定的渠道',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_group_def',
    @level2type = N'COLUMN',
    @level2name = N'group_type'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'group_type的关联ID',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_group_def',
    @level2type = N'COLUMN',
    @level2name = N'group_type_att_data'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示顺序',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_group_def',
    @level2type = N'COLUMN',
    @level2name = N'show_order'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示的平台 &0x01=PC平台 &0x02=IOS平台显示 &0x04=android平台 &0x08预留',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_group_def',
    @level2type = N'COLUMN',
    @level2name = N'show_platform'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'状态 0无效 1有效',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_group_def',
    @level2type = N'COLUMN',
    @level2name = 'show_state'