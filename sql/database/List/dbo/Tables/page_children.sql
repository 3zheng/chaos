CREATE TABLE [dbo].[page_children]
(
	[record_id] INT NOT NULL PRIMARY KEY IDENTITY, 
    [page_id] INT NOT NULL, 
    [group_id] INT NOT NULL, 
    [notes] VARCHAR(100) NULL, 
    [show_order] INT NOT NULL DEFAULT 0 
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'入口ID',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'page_children',
    @level2type = N'COLUMN',
    @level2name = N'page_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'大组ID',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'page_children',
    @level2type = N'COLUMN',
    @level2name = N'group_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'附加说明',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'page_children',
    @level2type = N'COLUMN',
    @level2name = 'notes'
GO

GO

EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示顺序',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'page_children',
    @level2type = N'COLUMN',
    @level2name = N'show_order'