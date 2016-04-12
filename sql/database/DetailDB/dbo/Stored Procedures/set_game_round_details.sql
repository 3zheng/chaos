CREATE PROCEDURE [dbo].[set_game_round_details]
	@xmlDoc xml
AS
	--表变量
	declare @plan_id int, @match_id bigint, @round_id varchar(50)
	declare	@round_details varchar(max), @game_kind int
	--临时变量
	declare @count int, @i int, @parm nvarchar(10), @sql nvarchar(200)
	set @i = 1
	set @count = @xmlDoc.value('(/root/count)[1]', 'int')
	while @i <= @count
	begin
		set @i = @i + 1;	--循环次数+1
		set @parm = @i;
		--取plan_id
		set @sql = N'select @plan_id = @xmlDoc.value(''(/root/data/plan_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@plan_id int output, @xmlDoc xml',@plan_id output, @xmlDoc
		--取match_id
		set @sql = N'select @match_id = @xmlDoc.value(''(/root/data/match_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@match_id bigint output, @xmlDoc xml',@match_id output, @xmlDoc
		--取round_id
		set @sql = N'select @round_id = @xmlDoc.value(''(/root/data/round_id)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@round_id varchar(50) output, @xmlDoc xml',@round_id output, @xmlDoc
		--取round_details
		set @sql = N'select @round_details = @xmlDoc.value(''(/root/data/round_details)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@round_details varchar(max) output, @xmlDoc xml',@round_details output, @xmlDoc
		--取game_kind
		set @sql = N'select @game_kind = @xmlDoc.value(''(/root/data/game_kind)[' + @parm + ']'', ''varchar(max)'')'
		exec sp_executesql @sql,N'@game_kind int output, @xmlDoc xml',@game_kind output, @xmlDoc
		

		insert into game_round_details(plan_id, match_id, round_id, round_details, game_kind)
			values(@plan_id, @match_id, @round_id, @round_details, @game_kind)

	end
RETURN 0
