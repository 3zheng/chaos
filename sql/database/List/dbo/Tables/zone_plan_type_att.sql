CREATE TABLE [dbo].[zone_plan_type_att]
(
	[plan_id] INT NOT NULL, 
    [att_id] INT NOT NULL 
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'zone_plan_def里的plan_type关联的id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_type_att',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'对应zone_plan_def里的plan_id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_type_att',
    @level2type = N'COLUMN',
    @level2name = N'plan_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'关联id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_plan_type_att',
    @level2type = N'COLUMN',
    @level2name = N'att_id'