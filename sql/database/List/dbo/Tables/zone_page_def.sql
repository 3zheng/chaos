CREATE TABLE [dbo].[zone_page_def]
(
	[page_id] INT NOT NULL PRIMARY KEY, 
    [page_name] NVARCHAR(50) NOT NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛区第一层级【页】',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_page_def',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'主键id，【页】码',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_page_def',
    @level2type = N'COLUMN',
    @level2name = 'page_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'【页】名',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'zone_page_def',
    @level2type = N'COLUMN',
    @level2name = 'page_name'