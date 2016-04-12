CREATE TABLE [dbo].[zone_list_type_att]
(
	[list_id] INT NOT NULL, 
    [att_id] INT NOT NULL 
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'zone_list_def中的list_type关联的id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_list_type_att',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'对应的zone_list_id中的list_id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_list_type_att',
    @level2type = N'COLUMN',
    @level2name = N'list_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'相关联的id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_list_type_att',
    @level2type = N'COLUMN',
    @level2name = N'att_id'