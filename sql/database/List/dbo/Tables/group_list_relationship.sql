CREATE TABLE [dbo].[group_list_relationship]
(
	[record_id] INT NOT NULL PRIMARY KEY IDENTITY(1, 1), 
    [list_id] INT NOT NULL, 
    [group_id] INT NOT NULL, 
    [show_state] INT NOT NULL DEFAULT 1, 
    [show_order] INT NOT NULL DEFAULT 0, 
    [notes] VARCHAR(100) NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'状态 0无效 1有效',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'group_list_relationship',
    @level2type = N'COLUMN',
    @level2name = 'show_state'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'【列表】id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'group_list_relationship',
    @level2type = N'COLUMN',
    @level2name = N'list_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'所属的【组】id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'group_list_relationship',
    @level2type = N'COLUMN',
    @level2name = 'group_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示顺序',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'group_list_relationship',
    @level2type = N'COLUMN',
    @level2name = N'show_order'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'说明',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'group_list_relationship',
    @level2type = N'COLUMN',
    @level2name = N'notes'