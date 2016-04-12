CREATE TABLE [dbo].[zone_list_def]
(
	[list_id] INT NOT NULL identity(10,1) PRIMARY KEY, 
    [list_name] NVARCHAR(50) NOT NULL, 
    [list_type] INT NOT NULL DEFAULT 1, 
    [show_order] INT NOT NULL DEFAULT 1, 
    [show_platform] INT NOT NULL DEFAULT 0xf, 
    [create_time] DATETIME NOT NULL DEFAULT getdate(), 
    [show_state] INT NOT NULL DEFAULT 1
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛区第三层级，【列表】',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_list_def',
    @level2type = N'COLUMN',
    @level2name = N'list_name'
GO

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'=1 表示这是固定类，所有的客户端都显示的 =2表示网吧类，根据IP显示 =3表示版本类，只显示给某个特定的版本',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_list_def',
    @level2type = N'COLUMN',
    @level2name = N'list_type'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示顺序',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_list_def',
    @level2type = N'COLUMN',
    @level2name = N'show_order'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示的平台 &0x01=PC平台 &0x02=IOS平台显示 &0x04=android平台 &0x08越狱IOS平台',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_list_def',
    @level2type = N'COLUMN',
    @level2name = N'show_platform'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'状态 0无效 1有效',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_list_def',
    @level2type = N'COLUMN',
    @level2name = 'show_state'