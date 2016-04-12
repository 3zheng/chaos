CREATE TABLE [dbo].[system_config]
(
	[r_id] INT NOT NULL PRIMARY KEY IDENTITY, 
    [item_name] VARCHAR(128) NULL, 
    [item_value] BIGINT NULL, 
    [item_string] VARCHAR(512) NULL, 
    [item_tips] VARCHAR(200) NULL, 
    [item_notes] VARCHAR(200) NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'记录id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'system_config',
    @level2type = N'COLUMN',
    @level2name = N'r_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'项目名称',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'system_config',
    @level2type = N'COLUMN',
    @level2name = N'item_name'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'项目整数值',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'system_config',
    @level2type = N'COLUMN',
    @level2name = N'item_value'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'项目字符串值',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'system_config',
    @level2type = N'COLUMN',
    @level2name = N'item_string'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'项目提示',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'system_config',
    @level2type = N'COLUMN',
    @level2name = N'item_tips'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'项目说明',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'system_config',
    @level2type = N'COLUMN',
    @level2name = N'item_notes'