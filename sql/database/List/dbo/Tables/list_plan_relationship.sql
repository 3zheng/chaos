CREATE TABLE [dbo].[list_plan_relationship]
(
	[record_id] INT NOT NULL PRIMARY KEY identity(1,1), 
    [plan_id] INT NOT NULL, 
    [list_id] INT NOT NULL, 
    [show_state] INT NOT NULL DEFAULT 1
	CONSTRAINT [CK_list_plan_relationship_unique] unique([plan_id],[list_id]), 
    [show_order] INT NOT NULL DEFAULT 0, 
    [notes] VARCHAR(100) NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'记录序号',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'list_plan_relationship',
    @level2type = N'COLUMN',
    @level2name = N'record_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛事id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'list_plan_relationship',
    @level2type = N'COLUMN',
    @level2name = N'plan_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'所属的【列表】id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'list_plan_relationship',
    @level2type = N'COLUMN',
    @level2name = N'list_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'状态 0无效 1有效',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'list_plan_relationship',
    @level2type = N'COLUMN',
    @level2name = 'show_state'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'显示顺序',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'list_plan_relationship',
    @level2type = N'COLUMN',
    @level2name = N'show_order'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'说明',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'list_plan_relationship',
    @level2type = N'COLUMN',
    @level2name = N'notes'